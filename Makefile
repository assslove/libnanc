FLAGS = -g -Wall
INCLUDE = 
LIBS = 

all : test_log
	#gcc -o test_log test_log.o -I./src -L./src -lnanc

test_log.o : test_log.c
	gcc -g -Wall -c test_log.c -I./src
test_log : test_log.c
	gcc -g -Wall -o test_log test_log.c -I./src -L./src -lnanc

clean : 
	rm -f *.o test_log
