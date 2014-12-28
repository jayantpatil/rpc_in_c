all: server client
server:
	gcc -c backup.c -o backup.o
	gcc -c server_stub.c -o server_stub.o 
	gcc server_stub.o backup.o -o server_stub

client:
	gcc -c user_program.c -o user_program.o
	gcc -c client_stub.c -o client_stub.o 
	gcc user_program.o client_stub.o -o user