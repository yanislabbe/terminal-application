const express = require('express');
const { spawn } = require('child_process');
const path = require('path');
const { promisify } = require('util');

const app = express();
app.use(express.json());
app.use(express.static('public'));

const port = 5000;

app.post('/execute', async (req, res) => {
  const command = req.body.command.trim();
  const folder = req.body.folder.trim();
  const isValidCommand = validateCommand(command);

  if (!isValidCommand) {
      return res.status(400).send('Invalid command');
  }

  const childProcess = spawn(command, { shell: true, cwd: path.join(__dirname, folder) });

  const [stdout, stderr] = await Promise.all([
    captureProcessOutput(childProcess.stdout),
    captureProcessOutput(childProcess.stderr),
  ]);

  try {
    await waitForProcessExit(childProcess);
    res.send(stdout);
  } catch (error) {
    console.error(`Error output: ${stderr}`);

    let errorMessage = error.message;
    if (error.code === 127) {
      errorMessage = `Command not found: ${command}`;
    }

    res.status(500).send(`${errorMessage}`);
  }
});

function validateCommand(command) {
  return true;
}

function captureProcessOutput(stream) {
  return new Promise((resolve, reject) => {
    let output = '';
    stream.on('data', (data) => {
      output += data.toString();
    });
    stream.on('end', () => {
      resolve(output);
    });
    stream.on('error', (error) => {
      reject(error);
    });
  });
}

function waitForProcessExit(childProcess) {
  return new Promise((resolve, reject) => {
    childProcess.on('close', (code) => {
      if (code === 0) {
        resolve();
      } else {
        const error = new Error('Child process exited with non-zero code');
        error.code = code;
        reject(error);
      }
    });
    childProcess.on('error', (error) => {
      reject(error);
    });
  });
}

app.listen(port, '0.0.0.0', () => {
  console.log(`Server is running on port ${port}`);
});
