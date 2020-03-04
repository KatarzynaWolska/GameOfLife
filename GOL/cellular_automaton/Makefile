all: cc test
cc: ca.o test_ca.c ../drawing/draw.o saving
	$(CC) -std=c11  ca.o test_ca.c ../drawing/draw.o ../saving/save.o -o test_ca -lpng 

test: cc
	./test_ca
saving: save.o
	$(CC) -std=c11 -c ../saving/save.c -o ../saving/save.o 

ca.o: ca.c ca.h
../drawing/draw.o: ../drawing/draw.c ../drawing/draw.h
save.o: ../saving/save.c ../saving/save.h

