#include "reader.h"
#define MAXLINELENGHT 256
#define ASCII0CODE 48

int check_first_line (char *line, int grid_reference[2]) {
	int height, width = 0;
	int i = 0;

	while((isspace(line[i]) != 0) && (line[i] != '\n'))
		i++;

	if(line[i] == '\n')
		return 1;	

	if(line[i] != '\0') {
		if(isdigit(line[i]) == 0) {
			return -1;
		}
		else {
			height = ((int)line[i] - ASCII0CODE)*10;
		}
	} else 
		return -1;

		i++;	
	
	if(line[i] != '\0') {
		if((isdigit(line[i]) == 0)) {
			return -1;
		}
		else {
			height += ((int)line[i] - ASCII0CODE);
		}
	} else
		return -1;

	i++;
	
	while(isspace(line[i]) != 0)
		i++;
	
	if((line[i] == '\0') || (line[i] != 'x')) 
		return -1;

	i++;
	
	while(isspace(line[i]) != 0)
		i++;

	if(line[i] != '\0') {
		if(isdigit(line[i]) == 0)
			return -1;
		else {
			width = ((int)line[i] - ASCII0CODE)*10;
		}
	} else 
		return -1;

	i++;
	
	if(line[i] != '\0') {
		if(isdigit(line[i]) == 0) 
				return -1;
		else {
			width += ((int)line[i] - ASCII0CODE);
		}
	} else
		return -1;


	i++;

	while(line[i] != '\n') {
		if(isspace(line[i]) == 0) 
			return -1; 
	
		i++;
	}
	grid_reference[0] = height;
	grid_reference[1] = width;

	return 0;
} 


int check_line (char *line, int grid_reference[2]) {
	int height, width = 0;
	int i = 0;

	while((isspace(line[i]) != 0) && (line[i] != '\n'))
		i++;

	if(line[i] == '\n')
		return 1;	

	if(line[i] != '(' || line[i] == '\0')
		return -1; 

	i++;

	while(isspace(line[i]) != 0)
		i++;
	
	if(line[i] != '\0') {
		if(isdigit(line[i]) == 0)
			return -1;
		else {
			height = ((int)line[i] - ASCII0CODE)*10;
		}
	} else 
		return -1;

	i++;
	
	if(line[i] != '\0') {
		if((isdigit(line[i]) == 0)) {
			return -1;
		}
		else {
			height += ((int)line[i] - ASCII0CODE);
		}
	} else
		return -1;

	i++;

	while(isspace(line[i]) != 0)
		i++;	
	
	if((line[i] == '\0') || (line[i] != ',')) 
		return -1;

	i++;

	while(isspace(line[i]) != 0)
		i++;	

	if(line[i] != '\0') {
		if(isdigit(line[i]) == 0)
			return -1;
		else {
			width = ((int)line[i] - ASCII0CODE)*10;
		}
	} else 
		return -1;

	i++;
	
	if(line[i] != '\0') {
		if(isdigit(line[i]) == 0) 
				return -1;
		else {
			width += ((int)line[i] - ASCII0CODE);
		}
	} else
		return -1;

	i++;

	while(isspace(line[i]) != 0)
		i++;	

	if(line[i] != ')' || line[i] == '\0')
		return -1;

	i++;

	while(line[i] != '\0') {
		if(isspace(line[i]) == 0) 
			return -1; 
	
		i++;
	}
	grid_reference[0] = height;
	grid_reference[1] = width;

	return 0;
} 

int read_file (char *inputname, generation_t *gen) {
	char values[MAXLINELENGHT];
	int coordinates[2];
	int height, width, check;
	FILE *in = fopen(inputname, "r");
	char *help_text = malloc(sizeof (*help_text) * 200);

	sprintf(help_text, "Poprawny format pliku:\n\n<h>x<w>:\n\n(x1,y1)\n...\n(xn,yn)\n\ngdzie:\nh - wysokość, w-szerokość\nx1...xn należą do <0;h)\ny1...yn należą do <0;w)\n\n");

	if( in == NULL ) {
		fprintf(stderr, "\nNie można otworzyć pliku %s.\n\n%s", inputname, help_text);
		return -1; 
	}

	while(fgets(values, MAXLINELENGHT-1, in) != NULL) {
		if((check = check_first_line(values, coordinates)) == -1) {
			fprintf(stderr, "\nBłąd w strukturze pliku.\n%s", help_text);
			fclose(in);
			return -2;
		}
		
		if(check == 1)
			continue;

		break;
	}

	height = coordinates[0];
	width = coordinates[1];

	if (fgets(values, MAXLINELENGHT-1, in) == NULL) {
		fprintf(stderr, "\nNie podano żadnych żywych komórek.\n%s", help_text);
		fclose(in);
		return -3;
	}


	*gen = init_matrix (height, width);

	while(fgets(values, MAXLINELENGHT-1, in) != NULL) {
		if((check = check_line(values, coordinates)) == -1 ) {
			fprintf(stderr, "\nBłąd w strukturze pliku.\n%s", help_text);
			clean_generation(*gen);
			fclose(in);
			return -2;
		}
	
		if(check == 1)
			continue;
		
		if(coordinates[0] >= height || coordinates[1] >= width) {
			fprintf(stderr, "\nJedna z wartości podanych w pliku jest spoza podanego na początku zakresu.\n%s", help_text);
			clean_generation(*gen);
			fclose(in);
			return -4;
		}

		add_living_cells(*gen, coordinates[0], coordinates[1]);
	}

 	free(help_text);
	fclose(in);
	return 0;
}
		

	
	
		
