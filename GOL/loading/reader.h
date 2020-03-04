#ifndef _READER_H_
#define _READER_H_
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../cellular_automaton/ca.h"

int check_line (char *line, int grid_reference[2]); 

int check_first_line (char *line, int grid_reference[2]); 

int read_file (char *inputname, generation_t *gen);

#endif
