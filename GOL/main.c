#include "cellular_automaton/ca.h"
#include "loading/reader.h"

int main(int argc, char **argv ){
	int read;
	char *inp;
	char *gif_name =  argc > 3 && strlen(argv[3]) <= 25 ? argv[3] : "GameOfLife.gif";
	int gen_num;
	generation_t gen = NULL;
	char *help_text = malloc(sizeof (*help_text) * 540);

	sprintf(help_text, "Aby poprawnie uruchomić program należy podać 2 bądź 3 argumenty:\n1. nazwę pliku konfiguracyjnego\n2. liczbę generacji \n3. nazwę pliku gif z grą (argument opcjonalny; max. 25 znaków - w razie przekroczenia zostanie użyta nazwa domyślna)\n\nUwaga: Jesli nie posiadasz programu ImageMagick gif z grą nie zostanie utworzony.\n\nPoprawny format pliku:\n\n<h>x<w>:\n\n(x1,y1)\n...\n(xn,yn)\n\ngdzie:\nh - wysokość, w-szerokość\nx1...xn należą do <0;h)\ny1...yn należą do <0;w)\n\n"); 

	if(argc < 2) {
		fprintf(stderr, "\n[%s]: Nie podano argumentu wejsciowego.\n\n%s", argv[0], help_text);
		return -1;
	}  
	
	if(argc < 3) {
		fprintf(stderr, "\n[%s]: Nie podano liczby generacji.\n\n%s ", argv[0], help_text);
		return -1;
	}
	
	if(atoi(argv[2]) != atof(argv[2]) || atoi(argv[2]) <= 0 || atoi(argv[2]) > 999){
		fprintf(stderr, "\n[%s]: Liczba generacji (drugi argument) powinna być liczbą całkowitą dodatnią.\n\n%s ", argv[0], help_text);
		return -1;
	}

	if(argc > 4)
		fprintf(stderr, "\n[%s]: Zbyt duża liczba argumentów. \n\n%s",argv[0], help_text);

	inp = argv[1];
	gen_num = atoi(argv[2]);

	read = read_file(inp, &gen);
	
	if(read < 0 ){ 
		return -1;
	}	

	next_generations(gen, gen_num, gif_name);
	free(help_text);	

	return 0;
}
