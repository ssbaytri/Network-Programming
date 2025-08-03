from PyQt5.QtWidgets import QWidget, QVBoxLayout, QTextEdit, QLineEdit, QPushButton, QApplication, QInputDialog, QLabel
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

        self.setWindowTitle("💬 Modern TCP Chat Room")
        self.resize(400, 550)
        self.setup_ui()
        self.setStyleSheet(self.load_stylesheet())
        self.get_nickname()
        self.connect_to_server()

    def get_nickname(self):
        nickname, ok = QInputDialog.getText(self, 'Nickname', 'Choose your nickname:')
        if ok and nickname:
            self.nickname = nickname
        else:
            self.nickname = "Anonymous"

    def connect_to_server(self):
        self.host = "127.0.0.1"
        self.port = 5050

        try:
            self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.client.connect((self.host, self.port))
            threading.Thread(target=self.receive_msg, daemon=True).start()
        except Exception as e:
            self.chat_display.append(f"❌ Failed to connect to server: {e}")

    def setup_ui(self):
        title = QLabel("Modern Chat Room")
        title.setAlignment(Qt.AlignCenter)
        title.setStyleSheet("font-size: 24px; font-weight: bold; margin-bottom: 10px;")

        self.chat_display = QTextEdit()
        self.chat_display.setReadOnly(True)

        self.input_field = QLineEdit()
        self.input_field.setPlaceholderText("Type your message here...")
        self.input_field.returnPressed.connect(self.send_msg)

        self.send_btn = QPushButton("Send")
        self.send_btn.clicked.connect(self.send_msg)

        layout = QVBoxLayout()
        layout.addWidget(title)
        layout.addWidget(self.chat_display)
        layout.addWidget(self.input_field)
        layout.addWidget(self.send_btn)

        self.setLayout(layout)

    def receive_msg(self):
        while True:
            try:
                message = self.client.recv(1024).decode("ascii")
                if message == "NICK":
                    self.client.send(self.nickname.encode("ascii"))
                else:
                    self.chat_display.append(message)
            except Exception as e:
                self.chat_display.append(f"⚠️ Connection lost: {e}")
                break

    def send_msg(self):
        if self.client and self.input_field.text().strip():
            message = f"{self.nickname}: {self.input_field.text()}"
            try:
                self.client.send(message.encode("ascii"))
                self.input_field.clear()
            except Exception as e:
                self.chat_display.append(f"⚠️ Failed to send message: {e}")

    def closeEvent(self, event):
        if self.client:
            self.client.close()
        event.accept()

    def load_stylesheet(self):
        return """
        QWidget {
            background-color: #1e1e2f;
            color: #ffffff;
            font-family: 'Segoe UI', sans-serif;
            font-size: 14px;
        }

        QTextEdit {
            background-color: #2c2c3c;
            border: 1px solid #3e3e50;
            border-radius: 8px;
            padding: 10px;
        }

        QLineEdit {
            background-color: #2c2c3c;
            border: 1px solid #3e3e50;
            border-radius: 8px;
            padding: 8px;
        }

        QLineEdit:focus {
            border: 1px solid #5c6bc0;
        }

        QPushButton {
            background-color: #5c6bc0;
            color: white;
            border-radius: 8px;
            padding: 8px;
        }

        QPushButton:hover {
            background-color: #7986cb;
        }

        QPushButton:pressed {
            background-color: #3f51b5;
        }

        QLabel {
            color: #ffffff;
        }
        """

if __name__ == "__main__":
    import sys
    app = QApplication(sys.argv)
    client = ChatClient()
    client.show()
    sys.exit(app.exec_())
