CC=gcc
CFLAGS=-Wall -pedantic
LDFLAGS=-Wall -pedantic

all: compile

clean:
	rm -rf client/client
	rm -rf server/server
	rm -rf algoritmo/algoritmo	

compile:
	$(CC) -o server/server server/server.c $(CFLAGS)
	$(CC) -o client/client client/client.c $(CFLAGS)
	$(CC) -o algoritmo/algoritmo algoritmo/algoritmo.c $(CFLAGS)
