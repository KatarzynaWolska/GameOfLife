CC = gcc
all: cc module_tests test
cc: main.c loading/reader.o cellular_automaton/ca.o saving drawing/draw.o
	$(CC) -ggdb -std=c11 main.c saving/save.o loading/reader.o cellular_automaton/ca.o drawing/draw.o -o GameOfLife -lpng -Wall
loading: loading/reader.o
	$(CC) -std=c11 -c loading/reader.c -o loading/reader.o 
saving: save.o
	$(CC) -std=c11 -c saving/save.c -o saving/save.o 
drawing: drawing/draw.o
	$(CC) -std=c11 -c drawing/draw.c -o drawing/draw.o -lpng
ca: cellular_automaton/ca.o
	$(CC) -std=c11 -c cellular_automaton/ca.c -o cellular_automaton/ca.o -lpng
clean:
	rm loading/*.o
	rm cellular_automaton/*.o
	rm drawing/*.o
	rm saving/*.o
test: cc
	./GameOfLife plik1 5 gol1.gif
	./GameOfLife plik2 140 gol2
	./GameOfLife plik3 60 
	make clean
module_tests: cc 
	cd saving/ && make
	make -C loading/
	make -C drawing/
	make -C cellular_automaton/
loading/reader.o: loading/reader.c loading/reader.h
save.o: saving/save.c saving/save.h 
drawing/draw.o: drawing/draw.c drawing/draw.h
cellular_automaton/ca.o: cellular_automaton/ca.c cellular_automaton/ca.h 
