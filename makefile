all: mouse

mouse: vlibo mouseo
	gcc vlib.o mouse_test.o -o mouse -lpthread
	rm vlib.o
	rm mouse_test.o

vlibo:
	as vlib.s -o vlib.o

mouseo:
	gcc -c mouse_test.c -o mouse_test.o -lpthread