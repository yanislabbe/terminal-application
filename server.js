const express = require('express');
const { spawn } = require('child_process');
const path = require('path');

const app = express();
app.use(express.json());
app.use(express.static('public'));

app.post('/execute', (req, res) => {
  try {
    const command = req.body.command.trim();
    const isValidCommand = validateCommand(command);

    if (!isValidCommand) {
      return res.status(400).send('Invalid command');
    }

    const childProcess = spawn(command, { shell: true, cwd: path.join(__dirname, 'program') });

    let output = '';
    let errorOutput = '';

    childProcess.stdout.on('data', (data) => {
      output += data.toString();
    });

    childProcess.stderr.on('data', (data) => {
      errorOutput += data.toString();
    });

    childProcess.on('close', (code) => {
      if (code === 0) {
        res.send(output);
      } else {
        res.status(500).send('Internal Server Error');
      }
    });
  } catch (error) {
    console.error(error);
    res.status(500).send('Internal Server Error');
  }
});

function validateCommand(command) {
  const trimmedCommand = command.trim();

  if (trimmedCommand.startsWith('make') || trimmedCommand.startsWith('./')) {
    return true;
  }

  return false;
}

const port = 5000;
app.listen(port, '0.0.0.0', () => {
  console.log(`Server is running on port ${port}`);
});
