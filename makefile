all: game

game: vlib.o game.o
	gcc vlib.o game.o -o game -lpthread
	rm vlib.o
	rm game.o

vlib.o:
	as src/lib/vlib.s -o vlib.o

game.o:
	gcc -c src/game.c -o game.o -lpthread