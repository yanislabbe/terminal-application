function writeToTerminal(text) {
    const terminal = document.getElementById('terminal');
    const lines = text.trim().split('\n');
    const formattedText = lines
        .map(line => {
            const formattedLine = line
                .replace(/\[1;33m/g, '<span style="color: yellow;">')
                .replace(/\[1;36m/g, '<span style="color: cyan;">')
                .replace(/\[1;34m/g, '<span style="color: blue;">')
                .replace(/\[1;32m/g, '<span style="color: green;">')
                .replace(/\[0m/g, '</span>');
            return `<p>${formattedLine}</p>`;
        })
        .join('');
    terminal.innerHTML += formattedText;
    terminal.scrollTop = terminal.scrollHeight;
}

function executeCommand(command) {
    const xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function() {
        if (xhr.readyState === 4) {
            if (xhr.status === 200) {
                const response = xhr.responseText;
                writeToTerminal(response);
            } else {
                const errorResponse = xhr.responseText;
                writeToTerminal(`Error: ${errorResponse}`);
            }
        }
    };

    xhr.open('POST', '/execute', true);
    xhr.setRequestHeader('Content-Type', 'application/json');
    xhr.send(JSON.stringify({ command: command }));
}

document.addEventListener('DOMContentLoaded', function() {
    const input = document.getElementById('commandInput');
    input.addEventListener('keydown', function(event) {
        if (event.key === 'Enter') {
            event.preventDefault();
            const command = input.value.trim();
            input.value = '';
            writeToTerminal(`$ ${command}`);
            executeCommand(command);
        }
    });
    input.focus();
});
