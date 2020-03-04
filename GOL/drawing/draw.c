#include "draw.h"

static png_byte color_type;
static png_byte bit_depth;
static int width;
static int height;
static png_structp png_ptr;
static png_infop info_ptr;

static png_bytep* process_file(int h, int w, int **matrix){
	width = 10 * w;
	height = 10 * h;
	bit_depth = 8;
	color_type = PNG_COLOR_TYPE_GRAY;
	int x, y, ry, rx;

	png_bytep *row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);

	for (y = 0; y < height; y++)
		row_pointers[y] = (png_byte*) malloc(sizeof(png_byte) * width);

	for (y = 0; y < height; y++) {
		png_byte* row = row_pointers[y];
		for (x = 0; x < width; x++) {
			rx = x % 10;
			ry = y % 10;
			row[x] = matrix[ ( y - ry ) / 10 ][ ( x - rx ) / 10 ] == 1 ? 255 : 0;
		}
	}

	return row_pointers;
}

void write_png_file(char *game_dir_name, int n_generation, int h, int w, int **matrix){
	char file_name[100]; 
	int y;

	sprintf(file_name, "%s/png_images/image%03d.png", game_dir_name, n_generation);

	png_bytep *row_pointers = process_file(h, w, matrix);

	FILE *fp = fopen(file_name, "wb");

	if (!fp)
		printf("[write_png_file] File %s could not be opened for writing", file_name);

	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if (!png_ptr)
		printf("[write_png_file] png_create_write_struct failed");

	info_ptr = png_create_info_struct(png_ptr);
 
	if (!info_ptr)
		printf("[write_png_file] png_create_info_struct failed");

	if (setjmp(png_jmpbuf(png_ptr)))
		printf("[write_png_file] Error during init_io");

	png_init_io(png_ptr, fp);

	if (setjmp(png_jmpbuf(png_ptr)))
		printf("[write_png_file] Error during writing header");

	png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

	png_write_info(png_ptr, info_ptr);

	if (setjmp(png_jmpbuf(png_ptr)))
		printf("[write_png_file] Error during writing bytes");

	png_write_image(png_ptr, row_pointers);

	if (setjmp(png_jmpbuf(png_ptr)))
		printf("[write_png_file] Error during end of write");

	png_write_end(png_ptr, NULL);

	for (y = 0; y < height; y++)
		free(row_pointers[y]);

	free(row_pointers);

	fclose(fp);

	if (png_ptr && info_ptr)
		png_destroy_write_struct(&png_ptr, &info_ptr);

}

