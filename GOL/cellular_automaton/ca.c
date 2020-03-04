#include "ca.h"
#include "../drawing/draw.h"
#include "../saving/save.h"

generation_t init_matrix (int rows_number, int elements_number) {
	int i, j;
	generation_t m = malloc (sizeof *(m));
	m->matrix = malloc (rows_number * sizeof *(m->matrix));
	for ( i = 0; i < rows_number; i++) {
		m->matrix[i] = malloc (elements_number * sizeof *(m->matrix[i])); 
		for ( j = 0; j < elements_number; j++) {
			m->matrix[i][j] = 0;
		}
	}
	m->height = rows_number;
	m->width = elements_number;
	return m;
}

void add_living_cells (generation_t gen, int height, int width) {
	gen->matrix[height][width]= 1;
}

int count_neighbours (generation_t gen, int i, int j) {
	int c = 0;

	if( (i-1) < 0 ) {
		if( (j-1) < 0 ) {
			if( gen->matrix[i][j+1] == 1)
				c++;

			if( gen->matrix[i+1][j+1] == 1)
				c++;

			if( gen->matrix[i+1][j] == 1)
				c++;
		}
		else if( (j+1) > ((gen->width)-1)) {
			if( gen->matrix[i+1][j] == 1)
				c++;
			
			if( gen->matrix[i+1][j-1] == 1)
				c++;

			if( gen->matrix[i][j-1] == 1)
				c++;
		}
		else {
			if( gen->matrix[i][j+1] == 1)
				c++;

			if( gen->matrix[i+1][j+1] == 1)
				c++;

			if( gen->matrix[i+1][j] == 1)
				c++;

			if( gen->matrix[i+1][j-1] == 1)
				c++;

			if( gen->matrix[i][j-1] == 1)
				c++;
		}
	}
	else if( (i+1) > ((gen->height) - 1)) {
		if( (j-1) < 0 ) {
			if( gen->matrix[i-1][j] == 1)
				c++;

			if( gen->matrix[i-1][j+1] == 1)
				c++;

			if( gen->matrix[i][j+1] == 1)
				c++;
		}
		else if( (j+1) > ((gen->width) - 1) ) {
			if( gen->matrix[i][j-1] == 1)
				c++;

			if( gen->matrix[i-1][j-1] == 1)
				c++;

			if( gen->matrix[i-1][j] == 1)
				c++;
		}
		else {
			if( gen->matrix[i][j-1] == 1)
				c++;

			if( gen->matrix[i-1][j-1] == 1)
				c++;

			if( gen->matrix[i-1][j] == 1)
				c++;

			if( gen->matrix[i-1][j+1] == 1)
				c++;

			if( gen->matrix[i][j+1] == 1)
				c++;
		}
	}
	else {
		if( (j-1) < 0 ) {
			if( gen->matrix[i-1][j] == 1)
				c++;

			if( gen->matrix[i-1][j+1] == 1)
				c++;

			if( gen->matrix[i][j+1] == 1)
				c++;

			if( gen->matrix[i+1][j+1] == 1)
				c++;

			if( gen->matrix[i+1][j] == 1)
				c++;
		}
		else if ( (j+1) > ((gen->width) - 1) ){
			if( gen->matrix[i-1][j] == 1)
				c++;

			if( gen->matrix[i-1][j-1] == 1)
				c++;

			if( gen->matrix[i][j-1] == 1)
				c++;

			if( gen->matrix[i+1][j-1] == 1)
				c++;

			if( gen->matrix[i+1][j] == 1)
				c++;
		}
		else {
			if( gen->matrix[i-1][j-1] == 1)
				c++;

			if( gen->matrix[i-1][j] == 1)
				c++;

			if( gen->matrix[i-1][j+1] == 1)
				c++;

			if( gen->matrix[i][j+1] == 1)
				c++;

			if( gen->matrix[i+1][j+1] == 1)
				c++;

			if( gen->matrix[i+1][j] == 1)
				c++;

			if( gen->matrix[i+1][j-1] == 1)
				c++;

			if( gen->matrix[i][j-1] == 1)
				c++;
		}
	}

	return c;
}
	
void swap_generations (generation_t **g1, generation_t **g2) {
	generation_t tmp = NULL;
	tmp = **g1;
	**g1 = **g2;
	**g2 = tmp;
}

int generations_equality (generation_t gen1, generation_t gen2) {
	int i,j;

	for(i = 0; i < gen1->height; i++) {
		for ( j = 0; j < gen1->width; j++){
			if((gen1->matrix[i][j]) != (gen2->matrix[i][j]))
				return 1;
		}
	}

	return 0;
}

void init_generations (generation_t *tmp, char **game_dir, generation_t g) {
	*game_dir = make_game_dir(*game_dir);
	*tmp = init_matrix(g->height, g->width);
	write_png_file(*game_dir, 0, g->height, g->width, g->matrix);
}

void finish_generations (generation_t gen, generation_t tmp, char *game_dir) {
	
	clean_generation(gen);
	clean_generation(tmp);
	free(game_dir);	
}

int make_generation (generation_t *tmp, generation_t *gen, char *game_dir, int actual_generation_number) {

	if( new_generation(*tmp, *gen) == 1) {
			printf("\nPrzedwcześnie skończono generowanie obrazków z powodu braku zmian w animacji.\nOstatnia przeprowadzona generacja ma numer %d.\n\n", actual_generation_number-1 );
			return 1;
		}
		swap_generations(&gen, &tmp);
		write_png_file(game_dir, actual_generation_number, (*gen)->height, (*gen)->width, (*gen)->matrix);
	return 0;
}

void make_gif_and_file (char *gif_name, char *game_dir, generation_t gen) {
	make_gif(gif_name, game_dir);
	save_into_file(game_dir, gen->height, gen->width, gen->matrix);	
}

void next_generations ( generation_t gen, int generations_number, char *gif_name) {  
	int i;
	generation_t tmp = NULL;
	char *game_dir;

	init_generations(&tmp, &game_dir, gen);
	
	for ( i = 1; i <= generations_number; i++) {
		if(make_generation(&tmp, &gen, game_dir, i) == 1)
			break;
	}

	make_gif_and_file (gif_name, game_dir, gen);
	
	finish_generations (gen, tmp, game_dir);
}

int change_state(generation_t gen, int height, int width, int nc) {
	if( gen->matrix[height][width] == 0) {
		if( nc == 3 ) 
			return 1;
		else
			return 0;
	}
	else {
		if( (nc == 2) || (nc == 3) ) 
			return 1;
		else		
			return 0;
	}
}
int new_generation (generation_t next_gen, generation_t actual_gen) {
	int i,j;
	int neigh_counter;	

	for (j = 0; j < actual_gen->height; j++) {
		for(i = 0; i < actual_gen->width; i++) {
			neigh_counter = count_neighbours (actual_gen, j, i); 
			change_state(actual_gen, j, i, neigh_counter) == 1 ? (next_gen->matrix[j][i] = 1) : (next_gen->matrix[j][i] = 0); 
		}			
	}

	if(generations_equality(next_gen, actual_gen) == 0 )
		return 1;

	return 0;
	
}


void clean_generation (generation_t gen) {
	int i;	

	for(i = 0; i < gen->height; i++) {
		free(gen->matrix[i]);
	}
	
	free(gen->matrix);
	free(gen);
}





	
