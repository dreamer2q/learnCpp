from socket import *

'''
这时一个非常简陋的HTTP Server，它唯一能做的就是提供了一个 GET 的文件请求
啊不想多说了，就这样吧，练练手熟悉一下 python 挺不错
'''

server_addr = ('0.0.0.0', 8080)

serv = socket(AF_INET, SOCK_STREAM)
# prepare a sever socket
serv.bind(server_addr)
serv.listen(10)

print("web server listen at {}".format(server_addr))
# loop, one by one
while True:
    # establish connection
    print('waiting for connection...')
    clntsock, clntaddr = serv.accept()
    print('clnt {}: connected'.format(clntaddr))
    try:
        reqbytes = clntsock.recv(2048).decode()
        req_path = reqbytes.split()[1]
        f = open(req_path[1:])
        outputdata = f.read()  # read file
        # Send one HTTP header line into socket
        # http status
        clntsock.send('HTTP/1.1 200 OK\r\n'.encode())
        # TODO send http headers
        clntsock.send('\r\n'.encode())  # http header over
        # begin the body
        clntsock.sendall(outputdata.encode())
        clntsock.close()  # end of http request
    except IOError as err:
        print('clnt {}: {}'.format(clntaddr, err))
        clntsock.send('HTTP/1.1 404 Not Found\r\n'.encode())
        # TODO send http headers
        clntsock.send('\r\n'.encode())  # http header over
        clntsock.close()
