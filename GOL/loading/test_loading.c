#include <stdio.h>
#include "reader.h"

int main (int argc, char **argv) {
	int i,x;
	char *input_name;
	int dimensions[2];
	generation_t g = NULL;
	dimensions[0] = 2;
	dimensions[1] = 2;
	int **living_cells;

	if( argc < 2 ) {
		printf("Nie podano nazwy pliku\n");
		return -1;
	}

	input_name = argv[1];

	x = read_file(input_name, &g); 
	
	if( (x == -1) || (x == -2) || (x == -3) || (x == -4) ) {
		clean_generation(g);	
		return -2;
	}

	living_cells = malloc(2 * sizeof(int *));

	for( i = 0; i < 2; i++) {
		living_cells[i] = malloc (2 * sizeof(int));
	}

	living_cells[0][0] = 1;
	living_cells[1][0] = 1;
	living_cells[0][1] = 1;
	living_cells[1][1] = 0;
	 


	printf("\n");
	
	if((g->height == dimensions[0]) && (g->width == dimensions[1]) && (g->matrix[0][0] == living_cells[0][0]) && (g->matrix[1][0] == living_cells[1][0]) && (g->matrix[0][1] == living_cells[0][1]) && (g->matrix[1][1] == living_cells[1][1])) {
		printf("loading: Testy modułu wczytującego wypadły pomyślnie.\n\n");
		clean_generation(g);
	}
	else {
		printf("loading: Testy modułu wczytującego wypadły niepomyślnie.\n\n");
		clean_generation(g);
	}

	for( i = 0; i < 2; i++) 
		free(living_cells[i]);		
	
	free(living_cells);
	return 0;
		
}
