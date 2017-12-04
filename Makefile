make default:
	gcc -pthread -lm client.c -o client
	gcc -pthread -lm server.c -o server
	gcc -o sorter_thread mergesort.c sorter_thread.c -g -lm -pthread
