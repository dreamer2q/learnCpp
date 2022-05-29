CLIENT_NAME=chat_client
SERVER_NAME=chat_server

CLIENT=udp_chat_client.c
SERVER=udp_chat_server.c

CC=gcc
CFLAGS=-Wformat -Wall -lpthread -lncursesw -I../../

all: chat_client chat_server

chat_client: $(CLIENT)
	$(CC) $(CFLAGS) $(CLIENT) -o $(CLIENT_NAME)

chat_server: $(SERVER)
	$(CC) $(CFLAGS) $(SERVER) -o $(SERVER_NAME)

.PHONY: clean all

clean:
	rm -f $(CLIENT_NAME) $(SERVER_NAME)
