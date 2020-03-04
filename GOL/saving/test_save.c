#include "save.h"

int if_file_exists(const char* fileName){
	FILE* file = fopen(fileName, "r");
    
	if (file == NULL){
		fclose(file);
		return -1;
	}

	fclose(file);
	return 0;
}
 	
int main(int argc, char **argv){
	int i, j, bug_counter = 0;
	char command[155];
	char *dir1, *dir2, *dir3;
	char gifname1 [30] = "1.gif";
	char gifname2[30] = "2";
	char tmp[105];
	dir1 = make_game_dir(dir1);
	dir2 = make_game_dir(dir2);
	dir3 = make_game_dir(dir3);

	int **matrix1 = malloc (sizeof *matrix1 * 14);
	int **matrix2 = malloc (sizeof *matrix2 * 3);
	int **matrix3 = malloc (sizeof *matrix3 * 70);

	if((strcmp(dir1, dir2) == 0) || (strcmp(dir1, dir3) == 0) || (strcmp(dir2, dir3) == 0)){
		fprintf(stderr, "\nsaving: Testy funkcji \"make_game_dir()\" nie powiodły się.\n");
		bug_counter++;
	}

	for( i = 0; i < 14 ;  i++){
		matrix1[i] = malloc(sizeof *(matrix1[i]) * 14);

		for(j = 0; j < 14 ; j++)
			matrix1[i][j] = (i+j % 3) == 1 ?  1 : 0;		
	}
	
	for( i = 0; i < 3 ;  i++){

		matrix2[i] = malloc(sizeof *(matrix2[i]) * 17);

		for(j = 0; j < 17 ; j++)
			matrix2[i][j] = (j % 3) == 0 ?  1 : 0;		
	}

	for( i = 0; i < 70 ;  i++){
		matrix3[i] = malloc(sizeof *(matrix3[i]) * 65);

		for(j = 0; j < 65 ; j++)
			matrix3[i][j] = (i % 4) == 1 ?  1 : 0;		
	}

	save_into_file("pngs_for_testing1", 14, 14, matrix1);
	save_into_file("pngs_for_testing2", 3, 17, matrix2);
	save_into_file(dir3, 70, 65, matrix3);

	if((if_file_exists("pngs_for_testing1/configurationfile.txt") == -1) || (if_file_exists("pngs_for_testing2/configurationfile.txt") == -1) || (if_file_exists("pngs_for_testing3/configurationfile.txt") == -1)){
		fprintf(stderr, "\nsaving: Testy funkcji \"save_into_file\" nie powiodły się.\n");
		bug_counter++;
	}

	sprintf(command, "rm -f -r %s %s %s", dir1, dir2, dir3);
	system(command);

	free(dir1);	
	free(dir2);
	free(dir3);
	
	for (i = 0; i < 14; i++)
		free(matrix1[i]);
	
	free(matrix1);

	for( i = 0; i < 3; i++)
		free(matrix2[i]);
	
	free(matrix2);

	for (i = 0; i < 70; i++)
		free(matrix3[i]);

	free(matrix3);
	
	make_gif(gifname1, "pngs_for_testing1");
	make_gif(gifname2, "pngs_for_testing2");
	
	sprintf(tmp, "pngs_for_testing1/%s", gifname1);
	
	if(if_file_exists(tmp) == -1){
		fprintf(stderr, "\nsaving: Testy funkcji \"make_gif\" nie powiodły się.\n");
		bug_counter++;
	}
		
	sprintf(tmp, "pngs_for_testing2/%s", gifname2);
	
	if(if_file_exists(tmp) == -1){
		fprintf(stderr, "\nsaving: Testy funkcji \"make_gif\" nie powiodły się.\n");
		bug_counter++;
	}
	
	
	if(bug_counter != 0){
		fprintf(stderr, "\nsaving: Testy modułu zapisującego nie przebiegły pomyślnie.\n\n");
		return -1;
	}
	
	fprintf(stderr, "\nsaving: Testy modułu zapisującego przebiegły pomyślnie.\n\n");

	return 0;
}
