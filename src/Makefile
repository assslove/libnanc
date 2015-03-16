# 生成C库
#

INSTALL_DIR = /usr/local/include/libnanc
CFLAGS =  -g -Wall -fPIC -Wunused-function -lpthread
OBJECTS = log.o util.o conf.o timer.o posix_lock.o random.o
LIBS = `pkg-config --cflags --libs glib-2.0`

all : libnanc.a libnanc.so

libnanc.a : $(OBJECTS)
	ar -cru libnanc.a $(OBJECTS)

libnanc.so : $(OBJECTS)
	gcc $(OBJECTS) -shared -o libnanc.so

%.o : %.c
	gcc $(CFLAGS) $(LIBS) -c  $< -o $@

clean:
	-rm $(OBJECTS) libnanc.a libnanc.so

install:
	#sudo cp -r libnanc.a /usr/local/lib
	sudo cp -r libnanc.so /usr/local/lib
	sudo rm -rf $(INSTALL_DIR)
	sudo mkdir $(INSTALL_DIR)
	sudo cp -r *.h $(INSTALL_DIR) 
