make default:
	gcc client.c -o client
	gcc server.c -o server
	gcc -o sorter_thread mergesort.c sorter_thread.c -g -lm -pthread