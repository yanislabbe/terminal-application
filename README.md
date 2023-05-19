# Terminal Application

This project is a simple terminal application that allows you to execute commands and display the results in a user interface.

## Prerequisites

Before you can use this application, make sure you have the following installed on your system:

- Node.js
- NPM (usually included with Node.js)

## Installation

Follow these steps to install and run the application:

1. Clone this repository to your local machine:

   ```bash
   git clone https://github.com/yanislabbe/terminal-application.git
   ```

2. Navigate to the project directory:

   ```bash
   cd terminal-application
   ```

3. Install the project dependencies using NPM:

   ```bash
   npm install
   ```

## Usage

To use the terminal application, follow these steps:

1. Launch the application by running the following command:

   ```bash
   npm start
   ```

2. Open your browser and navigate to the following URL:

   ```
   http://localhost:5000
   ```

3. You will now see a terminal interface in your browser.

4. Enter the commands you want to execute in the input field and press the `Enter` key.

5. The application will send the command to the server, which will execute it and send the results back to the terminal.

6. The command results will be displayed in the user interface terminal.

## Limitations

Please note the following limitations of this application:

- Only commands that involve calling external C programs with associated Makefiles are supported.
- External programs must be placed in the `program/` directory at the root of the project.
- Compilation or execution errors of the external programs will be displayed in the terminal.

## Contributing

Contributions to this project are welcome! If you would like to make improvements, bug fixes, or add new features, feel free to open a pull request.

Please make sure to test your changes and provide appropriate documentation.

## License

This project is licensed under the [MIT License](https://github.com/yanislabbe/terminal-application/blob/main/LICENSE).

---
