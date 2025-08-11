# TCP Chat Room

A multi-client TCP chat room application built with Python, featuring both command-line and GUI interfaces with modern styling.

## Features

- **Multi-client support**: Multiple users can connect and chat simultaneously
- **Real-time messaging**: Instant message delivery to all connected clients
- **Multiple client interfaces**:
  - Command-line interface for lightweight usage
  - Basic PyQt5 GUI for desktop users
  - Modern styled PyQt5 GUI with dark theme
- **Automatic nickname system**: Users choose their display names when connecting
- **Connection management**: Graceful handling of client connections and disconnections

## Repository Structure

```
├── server.py          # TCP server that handles all client connections
├── client.py          # Command-line chat client
├── ChatClient.py      # Basic PyQt5 GUI client
├── ModernChat.py      # Modern styled PyQt5 GUI client
└── README.md          # This documentation file
```

## Requirements

- Python 3.6+
- PyQt5 (for GUI clients only)

### Installing Dependencies

For command-line usage only:
```bash
# No additional dependencies required - uses built-in socket and threading modules
```

For GUI clients:
```bash
pip install PyQt5
```

## Usage

### 1. Start the Server

First, run the server to accept client connections:

```bash
python server.py
```

The server will start listening on `localhost:5050` and display:
```
Server is listening...
```

### 2. Connect Clients

You can connect multiple clients using any of the three available client interfaces:

#### Command-Line Client
```bash
python client.py
```
- Lightweight terminal-based interface
- Enter your nickname when prompted
- Type messages directly in the terminal

#### Basic GUI Client
```bash
python ChatClient.py
```
- Simple PyQt5 graphical interface
- Nickname input dialog on startup
- Text area for chat history and input field for messages

#### Modern GUI Client
```bash
python ModernChat.py
```
- Stylish dark-themed interface
- Modern UI with rounded corners and smooth interactions
- Enhanced visual feedback and professional appearance

## How It Works

### Server (`server.py`)
- Binds to localhost on port 5050
- Maintains lists of connected clients and their nicknames
- Broadcasts messages from one client to all other connected clients
- Handles client connections and disconnections gracefully
- Announces when users join or leave the chat

### Client Communication Protocol
1. Client connects to server
2. Server sends "NICK" request
3. Client responds with chosen nickname
4. Server broadcasts join message to all clients
5. Client can send messages in format: `nickname: message`
6. Server broadcasts all messages to connected clients

### GUI Clients (`ChatClient.py` & `ModernChat.py`)
- PyQt5-based graphical interfaces
- Thread-based message receiving to prevent UI blocking
- Automatic reconnection handling and error display
- Send messages by pressing Enter or clicking Send button

## Configuration

### Default Settings
- **Host**: `127.0.0.1` (localhost)
- **Port**: `5050`
- **Encoding**: ASCII
- **Buffer Size**: 1024 bytes

### Customizing Connection Settings

To change the host or port, modify these variables in the respective files:

**In server.py:**
```python
host = "127.0.0.1"  # Change to your desired host
port = 5050         # Change to your desired port
```

**In client files:**
```python
self.host = "127.0.0.1"  # Match server host
self.port = 5050         # Match server port
```

## Example Usage

1. **Start server:**
   ```bash
   python server.py
   ```

2. **Connect first client:**
   ```bash
   python ModernChat.py
   ```
   Enter nickname: "Alice"

3. **Connect second client:**
   ```bash
   python client.py
   ```
   Enter nickname: "Bob"

4. **Chat example:**
   ```
   Alice joined the chat!
   Bob joined the chat!
   Alice: Hello everyone!
   Bob: Hi Alice! How are you?
   Alice: I'm doing great, thanks for asking!
   ```

## Error Handling

The application includes robust error handling for:
- Connection failures
- Client disconnections
- Network interruptions
- Invalid input

Error messages are displayed in the chat interface with appropriate icons (🚫, ⚠️) in GUI versions.

## Limitations

- **Local network only**: Designed for localhost communication
- **No message history**: Messages are not persisted between sessions
- **No user authentication**: Basic nickname system without verification
- **ASCII encoding**: Limited character set support
- **No file sharing**: Text messages only

## Future Enhancements

Potential improvements could include:
- User authentication system
- Message encryption
- File sharing capabilities
- Chat rooms/channels
- Message history persistence
- Unicode/UTF-8 support
- Network configuration GUI
- User list display
- Private messaging

## Troubleshooting

### Common Issues

**"Connection refused" error:**
- Ensure the server is running before connecting clients
- Check that the host and port settings match between server and clients

**"Address already in use" error:**
- Another instance of the server is already running
- Wait a moment and try again, or change the port number

**GUI not displaying:**
- Ensure PyQt5 is installed: `pip install PyQt5`
- Check Python version compatibility

**Messages not appearing:**
- Verify network connection
- Check that all clients are using the same host/port configuration

## License

This project is open source and available under the MIT License.

## Contributing

Feel free to fork this repository and submit pull requests for any improvements or bug fixes.
