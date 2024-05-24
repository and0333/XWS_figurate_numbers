CFLAGS=$(math) $(xlib) $(debug) $(build)
math=-lm
debug=-g
xlib=-lX11
build=-o $(bdir)/$(name)
bdir=./build
name=Figurate-number
##-------------- object files
objects=FN-main.o FN-window-init.o FN-window-manage.o FN-calcs.o
##-------------- make
all: FN-main

FN-main: $(objects)
	gcc $(objects) $(CFLAGS)

FN-main.o: FN-main.c FN-window.h
	gcc -c FN-main.c $(debug)
FN-window-init.o: FN-window-init.c FN-window.h
	gcc -c FN-window-init.c $(debug)
FN-window-manage.o: FN-window-manage.c FN-window.h
	gcc -c FN-window-manage.c $(debug)
FN-calcs.o: FN-calcs.c FN-calcs.h
	gcc -c FN-calcs.c $(math) $(debug)

clean:
	rm -rf $(objects) $(bdir)/$(name)
rebuild: clean all 