all: zing zing2 

zing: main.o zing.o
	gcc -Wall main.o zing.o -o zing

zing2: main.o zing2.o
	gcc -Wall main.o zing2.o -o zing2

zing2.o: zing2.c
	gcc -Wall -c zing2.c -o zing2.o

main.o: main.c
	gcc -Wall -c main.c -o main.o

clean:
	rm main.o zing2.o zing zing2
