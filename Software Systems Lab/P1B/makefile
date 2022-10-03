all: main.o list.o queue.o
	gcc -o all main.o list.o queue.o

main.o: main.c list.h
	gcc -c main.c
list.o: list.c list.h
	gcc -c list.c
queue.o: queue.c queue.h
	gcc -c queue.c
	
clean: 
	rm all main.o
