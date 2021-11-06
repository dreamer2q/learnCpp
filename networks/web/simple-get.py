import sys
from socket import *

if len(sys.argv) != 3:
    print("usage: {} wwww.baidu.com 80 /".format(sys.argv[0]))
    exit(-1)

servaddr = sys.argv[1]
servport = int(sys.argv[2])
servpath = sys.argv[3]

req_get_line = 'GET {} HTTP/1.1\r\n'.format(servpath)

req_headers = {
    "User-Agent": "simple-get/python3.7",
}

# generate request header line
req_header_line = ''
for (key, val) in req_headers:
    req_header_line += '{}: {}\r\n'.format(key, val)
req_header_line += '\r\n'

print('request_header: {}'.format(req_header_line))

servsock = socket(AF_INET, SOCK_STREAM)
servsock.connect((servaddr, servport))

# creat connection
#Fill in start
#Fill in end
# encoding the message to binary bytes and send to server
#Fill in start
#Fill in end
data = 1
while data:
    data =  # Fill in start#Fill in end #receive message
    print(data.decode(), end='')

clientSocket.close()
