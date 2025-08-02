import threading
import socket

host = "127.0.0.1" # local host
port = 5050

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((host, port))
server.listen()

clinets = []
nicknames = []

def broadcast(message):
	for client in clinets:
		client.send(message)

def handle(client):
	while True:
		try:
			message = client.recv(1024)
			broadcast(message)
		except:
			index = clinets.index(client)
			clinets.remove(client)
			client.close()
			nickname = nicknames[index]
			broadcast(f'{nickname} has left the chat!'.encode('ascii'))
			nicknames.remove(nickname)
			break


