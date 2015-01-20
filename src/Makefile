CFLAGS =  -g -Wall -fPIC 
OBJECTS = log.o util.o

all : libnanc.a libnanc.so

libnanc.a : $(OBJECTS)
	ar -cru libnanc.a log.o util.o

libnanc.so : $(OBJECTS)
	gcc $< -shared -o libnanc.so

%.o : %.c
	gcc $(CFLAGS) -c  $< -o $@

clean:
	-rm $(OBJECTS) libnanc.a
