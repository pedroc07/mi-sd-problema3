all: game

game: vlib.o game.o
	gcc vlib.o game.o -o game -lpthread
	rm vlib.o
	rm game.o

mouse: vlib.o mouse.o
	gcc vlib.o mouse_test.o -o mouse -lpthread
	rm vlib.o
	rm mouse_test.o

vlib.o:
	as vlib.s -o vlib.o

mouse.o:
	gcc -c mouse_test.c -o mouse_test.o -lpthread

game.o:
	gcc -c game.c -o game.o -lpthread


