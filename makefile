ftserver: ftserver.o
		gcc -o ftserver ftserver.o

ftserver.o: ftserver.c str.o
		gcc -c ftserver.c

str.o: str.c
		gcc -c str.c

clean:
		-rm -f *.o
		-rm -f ftserver
