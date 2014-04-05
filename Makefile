CC=gcc
CFLAGS=-Wall -pedantic
LDFLAGS=-Wall -pedantic

all: compile

clean:
	rm -rf client/client
	rm -rf server/server
	rm -rf algoritmo/algoritmo.o algoritmo/algoritmo	

compile:
	$(CC) -c -o algoritmo/algoritmo.o algoritmo/algoritmo.c $(LDFLAGS)
	$(CC) -o server/server server/server.c algoritmo/algoritmo.o $(CFLAGS) 
	$(CC) -o client/client client/client.c algoritmo/algoritmo.o $(CFLAGS)


