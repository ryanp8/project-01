all: main.o input.o util.o
	gcc -o program main.o input.o util.o

main.o: main.c
	gcc -c main.c

input.o: input.c input.h
	gcc -c input.c

util.o: util.c util.h
	gcc -c util.c

clean:
	rm *.o
	rm program

run:
	./program