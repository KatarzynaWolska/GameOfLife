all: cc test
cc: reader.o test_loading.c ../cellular_automaton/ca.o ../drawing/draw.o saving
	$(CC) -std=c11 reader.o test_loading.c ../cellular_automaton/ca.o ../drawing/draw.o ../saving/save.o -o test_loading -lpng

test: cc
	./test_loading plik
saving: save.o
	$(CC) -std=c11 -c ../saving/save.c -o ../saving/save.o 

reader.o: reader.c reader.h
../cellular_automaton/ca.o: ../cellular_automaton/ca.c ../cellular_automaton/ca.h
../drawing/draw.o: ../drawing/draw.c ../drawing/draw.h
save.o: ../saving/save.c ../saving/save.h
