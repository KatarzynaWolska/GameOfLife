test: cc
	./test_drawing  
cc: draw.o test_draw.o
	$(CC) -std=c11 draw.o test_draw.o -o test_drawing -Wall -lpng
draw.o: draw.c draw.h
test_drawing.o: test_drawing.c
