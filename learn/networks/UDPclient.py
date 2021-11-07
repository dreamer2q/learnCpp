from socket import *

serverName = 'localhost'
serverPort = 12000

clientSocket = socket(AF_INET, SOCK_DGRAM)

message = input('Input lowercase sentences: ')

clientSocket.sendto(message.encode(), (serverName, serverPort))

recvMessage, serverAddr = clientSocket.recvfrom(2048)

print(recvMessage.decode())

clientSocket.close()
