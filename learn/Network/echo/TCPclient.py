from socket import *
from typing import Collection

serverName = 'localhost'
serverPort = 12000

clientSock = socket(AF_INET, SOCK_STREAM)

clientSock.connect((serverName, serverPort))

message = input('input lowercase sentence: ')

clientSock.send(message.encode())

recvMsg = clientSock.recv(2048)

print('recv reply: '+recvMsg.decode())

clientSock.close()
