#ifndef _CELL_AUTO_H_
#define _CELL_AUTO_H_
#include <stdlib.h>
#include <stdio.h>
#include "../saving/save.h"
#include "../drawing/draw.h"

typedef struct gen{
	int **matrix;
	int height;
	int width;
} *generation_t;	

generation_t init_matrix (int rows_number, int elements_number);
 
void add_living_cells (generation_t gen, int height, int width);

int count_neighbours (generation_t gen, int i, int j);
 
void next_generations ( generation_t gen, int generations_number, char *gif_name);

int change_state(generation_t gen, int height, int width, int nc);
 
int new_generation (generation_t next_gen, generation_t actual_gen);

void swap_generations (generation_t **g1, generation_t **g2);
 
int generations_equality (generation_t gen1, generation_t gen2);

void init_generations (generation_t *tmp, char **game_dir, generation_t g);

int make_generation (generation_t *tmp, generation_t *gen, char *game_dir, int actual_generation_number); 

void make_gif_and_file (char *gif_name, char *game_dir, generation_t gen);

void finish_generations (generation_t gen, generation_t tmp, char *game_dir); 

void clean_generation (generation_t gen);
 
#endif
