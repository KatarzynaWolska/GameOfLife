#include "draw.h"

int if_file_exists(const char* fileName){
	FILE* file = fopen(fileName, "r");
    
	if (file == NULL){
		fclose(file);
		return -1;
	}

	fclose(file);
	return 0;
}

int main(int argc, char **argv) {
	int i, j, bug_counter = 0;	
	int **matrix1 = malloc (sizeof *matrix1 * 14);
	int **matrix2 = malloc (sizeof *matrix2 * 3);
	int **matrix3 = malloc (sizeof *matrix3 * 70);
	
	for( i = 0; i < 14 ;  i++){
		matrix1[i] = malloc(sizeof *(matrix1[i]) * 14);

		for(j = 0; j < 14 ; j++)
			matrix1[i][j] = (i + j) % 3 == 1 ?  1 : 0;		
	}
	
	for( i = 0; i < 3 ;  i++){

		matrix2[i] = malloc(sizeof *(matrix2[i]) * 17);

		for(j = 0; j < 17 ; j++)
			matrix2[i][j] = j % 3 == 0 ?  1 : 0;		
	}

	for( i = 0; i < 70 ;  i++){
		matrix3[i] = malloc(sizeof *(matrix3[i]) * 65);

		for(j = 0; j < 65 ; j++)
			matrix3[i][j] = i % 4 == 1 ?  1 : 0;		
	}
		
	system("mkdir -p img/png_images");

	write_png_file( "img/", 1, 14, 14, matrix1 );
	write_png_file( "img/", 2, 3, 17, matrix2 );
	write_png_file( "img/", 3, 70, 65, matrix3 );

	if((if_file_exists("img/png_images/image001.png") == -1) || (if_file_exists("img/png_images/image001.png") == -1) || (if_file_exists("img/png_images/image001.png") == -1)){	
		fprintf(stderr, "\ndrawing: Testy funkcji \"write_png_file\" nie powiodły się.\n");		
		bug_counter++;
	}
	
	system("rm -r -f img");
	
	for (i = 0; i < 14; i++)
		free(matrix1[i]);
	
	free(matrix1);

	for( i = 0; i < 3; i++)
		free(matrix2[i]);
	
	free(matrix2);

	for (i = 0; i < 70; i++)
		free(matrix3[i]);

	free(matrix3);

	if(bug_counter != 0){
		fprintf(stderr, "\ndrawing: Testy modułu rysującego nie zakończyły się pomyślnie.\n\n");
		return -1;
	}

	fprintf(stderr, "\ndrawing: Testy modułu rysującego zakończyły się pomyślnie.\n\n");

	return 0;
}
