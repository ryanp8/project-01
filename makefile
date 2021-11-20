all: main.o trim.o
	gcc -o program main.o trim.o

main.o: main.c
	gcc -c main.c

trim.o: trim.c
	gcc -c trim.c

clean:
	rm *.o
	rm program

run:
	./program