#ifndef _SAVE_H
#define _SAVE_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char *make_game_dir(char *game_dir_name);

void save_into_file(char *game_dir_name, int height, int width, int **matrix);

void make_gif(char *gif_name, char *game_dir_name);

#endif
