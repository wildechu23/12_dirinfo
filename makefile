all: dirinfo.o
	gcc -o info dirinfo.o

dirinfo.o: dirinfo.c
	gcc -c dirinfo.c

run:
	./info