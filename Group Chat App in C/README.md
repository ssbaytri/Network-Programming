# Group Chat Application (C)

This project is a simple Group Chat (chatroom) application built in C, located in the `c/` folder. It demonstrates the use of sockets and TCP connections to enable multiple clients to communicate in real-time over a network.

## Features

- **Multi-client support:** Multiple clients can join the chatroom and exchange messages.
- **TCP-based communication:** Reliable message delivery using TCP sockets.
- **Broadcast messaging:** Messages from any client are relayed to all connected clients.
- **Simple command-line interface:** Both server and clients run in the terminal.
- **Basic user management:** Tracks and displays connected users.

## Project Structure

- `server.c`  
  Implements the chat server that handles client connections, message broadcasting, and user management.

- `client.c`  
  Implements the chat client, allowing users to connect to the server and send/receive messages.

- `Makefile`  
  For building the server and client binaries.

## How It Works

1. **Server Setup:**  
   The server listens on a specified port for incoming TCP connections from clients.

2. **Client Connection:**  
   Clients connect to the server by specifying the server's IP address and port.

3. **Message Handling:**  
   - Each client can send messages to the server.
   - The server receives each message and broadcasts it to all other connected clients.
   - The server manages client joins, disconnects, and ensures all clients receive updates.

## How to Build

```sh
cd c
make
```

This will produce two executables: `server` and `client`.

## Usage

### 1. Start the Server

```sh
./server <port>
```
- Example: `./server 8080`

### 2. Start Clients

In separate terminal windows (or different machines on the same network):

```sh
./client <server_ip> <port>
```
- Example: `./client 127.0.0.1 8080`

### 3. Chat!

- Each client can type messages and see messages from others in real time.
- To exit, use the designated quit command or close the client window (see code for details).

## Example

```
Server: Welcome to the Group Chat!
Alice: Hello everyone!
Bob: Hi Alice!
Charlie: Good afternoon!
```

## Requirements

- GCC (or compatible C compiler)
- Linux or Unix-like OS (code may need minor tweaks for Windows)
- Basic POSIX sockets support

## Notes

- This is a learning/demo project and does not implement advanced features such as authentication, encryption, or message history.
- For production, consider handling edge cases (e.g., client timeouts, large messages) and adding security features.

## License

This project is licensed under the MIT License.

---

*Happy chatting!*
