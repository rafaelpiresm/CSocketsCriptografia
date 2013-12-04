CC=g++
CFLAGS=-Wall -pedantic
LDFLAGS=-Wall -pedantic

all: compile

clean:
	rm -rf client/client

compile:
	$(CC) -o server server/server.c $(CFLAGS)
	$(CC) -o client client/client.c $(CFLAGS)
