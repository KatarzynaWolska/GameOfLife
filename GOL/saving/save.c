#include "save.h"

char *make_game_dir(char *game_dir_name){
	char command[75], nano_tmp[11];
	time_t current_time;
	struct tm * current_date;
	struct timespec t;
	timespec_get(&t, TIME_UTC);
	
	game_dir_name = malloc(sizeof (*game_dir_name) * 45);
	time(&current_time);
	current_date = localtime(&current_time);

	strftime(game_dir_name, 75, "GameResults_%Y.%m.%d_%H:%M:%S:", current_date);
	sprintf(nano_tmp, "%ld", t.tv_nsec);
	strcat(game_dir_name, nano_tmp);	

	sprintf(command, "mkdir -p %s/png_images", game_dir_name);
	system (command);

	return game_dir_name;
}

void save_into_file(char *game_dir_name, int height, int width, int **matrix){
	int i, j;
	char file_name[70];
	sprintf(file_name, "%s/configurationfile.txt", game_dir_name);
	FILE *file = fopen(file_name, "w");

	if(file == NULL){
		fprintf(stderr, "\nWystapił błąd przy tworzeniu pliku z zapisem generacji.\n\n");
		return;
	}

	fprintf(file, "%d x %d\n\n", height, width);

	for(i = 0; i < height; i++){	
		for(j = 0; j < width; j++){
			if(matrix[i][j] == 1)
				fprintf(file, "(%d, %d)\n", i, j); 
		}
	}

	fclose(file);	
}

void make_gif(char *gif_name, char *game_dir_name){
	char command[160];

	if(strstr( gif_name, ".gif") == NULL){
		gif_name = strcat(gif_name, ".gif"); 
	}

	sprintf(command, "convert -delay 10 -loop 0 %s/png_images/*.png %s/%s", game_dir_name, game_dir_name, gif_name);
	
	system(command);
}





