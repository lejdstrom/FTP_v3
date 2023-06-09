#CC = gcc
#FLAGS = -Wall -c -g -pthread

all: client server

client: client.o client_utils.o commons.o
	gcc -Wall -g client.o client_utils.o commons.o -o client

server: server.o server_utils.o commons.o
	gcc -Wall -g server.o server_utils.o commons.o -o server -pthread

commons.o: commons.c commons.h
	gcc -Wall -c -g commons.c

client.o: client.c client_utils.c commons.c
	gcc -Wall -c -g client.c client_utils.c commons.c

server.o: server.c server_utils.c commons.c
	gcc -Wall -c -g server.c server_utils.c commons.c

client_utils.o: client_utils.c client_utils.h
	gcc -Wall -c -g client_utils.c

server_utils.o: server_utils.c server_utils.h
	gcc -Wall -c -g server_utils.c

debug_client:
	gdb --args ./client 12345

debug_server:
	gdb --args ./server 12345

clean:
	@rm -f *.o server client