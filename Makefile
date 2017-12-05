make default:
	gcc -pthread -lm client.c -o client
	gcc -pthread -lm server.c -o server
