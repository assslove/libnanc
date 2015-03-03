FLAGS = -g -Wall
INCLUDE = 
LIBS = `pkg-config --cflags --libs glib-2.0`

all : test_util test_timer test_sem test_log
	#gcc -o test_log test_log.o -I./src -L./src -lnanc

test_log : test_log.c
	gcc -o test_log test_log.c -lpthread -L/usr/local/lib -lnanc  -g -Wall   $(LIBS) 
test_util: test_util.c
	gcc -g -Wall -o test_util test_util.c -I./src -L./src -lnanc
test_timer: test_timer.c
	gcc -g -Wall -o test_timer test_timer.c -I/usr/local/include/libnanc -lnanc $(LIBS)
test_sem: test_sem.c
	gcc -g -Wall -o test_sem test_sem.c -I/usr/local/include/libnanc -lnanc $(LIBS)

clean : 
	rm -f *.o test_log test_timer
