all : libnanc.a

libnanc.a : log.o
	ar -cru libnanc.a log.o

log.o: log.c
	gcc -g -Wall -O2 -c log.c

clean:
	rm *.o libnanc.a
