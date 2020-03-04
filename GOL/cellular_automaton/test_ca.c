#include <stdio.h>
#include <stdlib.h>
#include "ca.h"

void swap_generation_4_test (generation_t *g1, generation_t *g2) {
	generation_t tmp = NULL;
	tmp = *g1;
	*g1 = *g2;
	*g2 = tmp;
}

int main( int argc, char ** argv) {
	int dimensions[2] = {4, 4};
	generation_t g1 = NULL;
	generation_t g2 = NULL;
	generation_t g3 = NULL;
	int i;

	g1 = init_matrix(dimensions[0], dimensions[1]);
	g2 = init_matrix(dimensions[0], dimensions[1]);
	g3 = init_matrix(dimensions[0], dimensions[1]);

	add_living_cells (g1, 0, 1);
	add_living_cells (g1, 1, 2);
	add_living_cells (g1, 2, 0);
	add_living_cells (g1, 2, 1);
	add_living_cells (g1, 2, 2);

	new_generation(g2, g1);
	swap_generation_4_test(&g1, &g2);

	add_living_cells(g3, 1, 0);
	add_living_cells(g3, 1, 2);
	add_living_cells(g3, 2, 1);
	add_living_cells(g3, 2, 2);
	add_living_cells(g3, 3, 1);

	if(generations_equality(g1, g3) == 0) 
		printf("\ncellular_automaton: Testy automatu komórkowego wypadły pomyślnie.\n\n");
	else 
		printf("\ncellular_automaton: Testy automatu komórkowego wypadły niepomyślnie.\n\n");

	clean_generation(g1);
	clean_generation(g2);
	clean_generation(g3);

	return 0;
}
