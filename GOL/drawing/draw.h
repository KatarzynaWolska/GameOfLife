#ifndef _DRAW_H
#define _DRAW_H
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <png.h>

void write_png_file(char* game_dir_name, int n_generation, int h, int w, int **matrix);

#endif
