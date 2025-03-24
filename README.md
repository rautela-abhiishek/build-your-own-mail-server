```markdown
# Simple Mail Server in C

This repository contains the code for building a simple mail server using the C programming language. The project demonstrates how a basic mail server can receive and send emails using the SMTP protocol, handle incoming connections, and interact with email clients.

## Features
- SMTP Server: Simple implementation of an SMTP server to send and receive emails.
- IMAP Protocol: Support for the IMAP protocol to manage and retrieve emails from mailboxes.
- Multithreading: Basic multithreading to handle multiple email connections simultaneously.
- Command-line Interface (CLI): Allows you to interact with the server from the terminal.
  
## Requirements

Before using this project, ensure you have the following installed:

- GCC Compiler: A C compiler like GCC to compile the project.
- Make: To build and manage the project.
- Linux OS or WSL: The project has been tested on Linux-based operating systems. You can also use Windows Subsystem for Linux (WSL) on Windows.

## Setup Instructions

1. Clone the Repository:

   First, clone the repository to your local machine.

   ```bash
   git clone https://github.com/yourusername/simple-mail-server.git
   cd simple-mail-server
   ```

2. Install Dependencies:

   The project uses the `libssl` library for secure communication (TLS). Install it with the following commands on Ubuntu:

   ```bash
   sudo apt update
   sudo apt install libssl-dev
   ```

3. Build the Project:

   Use `make` to compile the project.

   ```bash
   make
   ```

4. Configuration:

   Edit the `config.h` file to set up your mail server configurations like port numbers and email domain.

   ```c
   #define SMTP_PORT 25
   #define IMAP_PORT 143
   #define DOMAIN "yourdomain.com"
   ```

## Usage

To start the server, simply run:

```bash
./mailserver
```

The server will start listening on the configured SMTP and IMAP ports. You can test it by connecting with an email client that supports SMTP and IMAP.

### Sending Email

To send an email, you can either use an email client or the included command-line tool `sendmail`:

```bash
./sendmail recipient@example.com "Subject Here" "Message Body Here"
```

### Checking Emails

To check your inbox using the IMAP protocol, use the `imapclient` tool:

```bash
./imapclient
```

It will prompt you to log in and then show the available emails in your inbox.

## File Structure

- `src/`: Contains the main source code for the server and client tools.
- `config.h`: Configuration file for server settings.
- `Makefile`: The build file to compile the project.
- `README.md`: Documentation for the project.

## Contributing

Contributions are welcome! If you'd like to contribute, please fork the repository and submit a pull request.

### Steps to Contribute:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature-branch`)
3. Make your changes
4. Commit your changes (`git commit -am 'Add new feature'`)
5. Push to the branch (`git push origin feature-branch`)
6. Open a Pull Request

## License

This project is licensed under the Apache2.0 License- see the [LICENSE](LICENSE) file for details.


