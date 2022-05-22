from socket import *

serverPort = 12000
serverSocket = socket(AF_INET, SOCK_DGRAM)
serverSocket.bind(('', serverPort))
print('server is ready :)')

while True:
    message, clientAddr = serverSocket.recvfrom(2048)
    modifiedMsg = message.decode().upper()
    serverSocket.sendto(modifiedMsg.encode(), clientAddr)
