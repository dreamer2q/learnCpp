all: httpd client

LIBS = -lpthread #-lsocket
INCS = -I../..

httpd: httpd.c
	gcc -g -W -Wall -o $@ $< $(LIBS) $(INCS)

# client: simpleclient.c
# 	gcc -W -Wall -o $@ $<

clean:
	rm httpd
