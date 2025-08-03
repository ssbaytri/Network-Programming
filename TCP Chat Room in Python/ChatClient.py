from PyQt5.QtWidgets import QWidget, QVBoxLayout, QTextEdit, QLineEdit, QPushButton, QApplication, QInputDialog
from PyQt5.QtCore import Qt
import socket, threading


class ChatClient(QWidget):
    def __init__(self):
        super().__init__()
        self.send_btn = None
        self.input_field = None
        self.chat_display = None
        self.client = None

        self.nickname = None

        self.setWindowTitle("TCP Chat Room")
        self.resize(400, 500)
        self.setup_ui()
        self.get_nickname()
        self.connect_to_server()

    def get_nickname(self):
        """Get nickname from user via input dialog"""
        nickname, ok = QInputDialog.getText(self, 'Nickname', 'Choose your nickname:')
        if ok and nickname:
            self.nickname = nickname
        else:
            self.nickname = "Anonymous"

    def connect_to_server(self):
        """Connect to the server and start receiving messages"""
        self.host = "127.0.0.1"
        self.port = 5050

        try:
            self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.client.connect((self.host, self.port))
            threading.Thread(target=self.receive_msg, daemon=True).start()
        except Exception as e:
            self.chat_display.append(f"Failed to connect to server: {e}")

    def setup_ui(self):
        """Set up the user interface"""
        self.chat_display = QTextEdit()
        self.chat_display.setReadOnly(True)

        self.input_field = QLineEdit()
        self.input_field.setPlaceholderText("Type your message here...")
        self.input_field.returnPressed.connect(self.send_msg)  # Send on Enter

        self.send_btn = QPushButton("Send")
        self.send_btn.clicked.connect(self.send_msg)

        layout = QVBoxLayout()
        layout.addWidget(self.chat_display)
        layout.addWidget(self.input_field)
        layout.addWidget(self.send_btn)

        self.setLayout(layout)

    def receive_msg(self):
        """Receive messages from the server"""
        while True:
            try:
                message = self.client.recv(1024).decode("ascii")
                if message == "NICK":
                    # Server is asking for nickname
                    self.client.send(self.nickname.encode("ascii"))
                else:
                    # Display the message in the chat
                    self.chat_display.append(message)
            except Exception as e:
                self.chat_display.append(f"Connection lost: {e}")
                break

    def send_msg(self):
        """Send message to the server"""
        if self.client and self.input_field.text().strip():
            message = f"{self.nickname}: {self.input_field.text()}"
            try:
                self.client.send(message.encode("ascii"))
                self.input_field.clear()
            except Exception as e:
                self.chat_display.append(f"Failed to send message: {e}")

    def closeEvent(self, event):
        """Handle window close event"""
        if self.client:
            self.client.close()
        event.accept()


if __name__ == "__main__":
    import sys
    app = QApplication(sys.argv)
    client = ChatClient()
    client.show()
    sys.exit(app.exec_())
