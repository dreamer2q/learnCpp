from socket import *

serverPort = 12000
serverSock = socket(AF_INET, SOCK_STREAM)

serverSock.bind(('', serverPort))
serverSock.listen(1)

print('server is ready :)')

while True:
    connSock, addr = serverSock.accept()
    recvMsg = connSock.recv(2048).decode()
    resMsg = recvMsg.upper().encode()
    connSock.send(resMsg)
    connSock.close()
