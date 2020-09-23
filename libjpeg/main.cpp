
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "pgm.h"
#include "jpeglib.h"


#define PGM_SIZE 8672*3680

char *pgmfile[] = {
	"test.pgm",
	"test.pgm",
	"test.pgm",

};

int main(int argc, char *argv[])
{
	
	pgm_parse pgm;
	unsigned char *pgm_data;
	unsigned char *jpg_data;
	char *apenfix;
	int ret;
	int pgm_fd;
	int jpg_fd;
	long unsigned int jpg_size;
	int pgm_size;
	char target_filename[100];
	
	pgm_data = (unsigned char *)malloc(PGM_SIZE);
	jpg_data = (unsigned char *)malloc(1*1000*1000);
	jpg_size = 1*1000*1000;

	struct pgm_entity pgms;
	

	//pgm_parse
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);


	int i;
	for (i = 0; i < sizeof(pgmfile)/sizeof(pgmfile[0]); i++) {

		//get pgm data
		pgms = pgm.parse(pgmfile[i]);

		//create jpg file
		memset(target_filename, 0, 100);
		strcpy(target_filename, pgmfile[i]);
		apenfix = strstr(target_filename, ".pgm");
		memcpy(apenfix, ".jpg", 4);
		jpg_fd = open(target_filename, O_RDWR|O_CREAT, S_IRWXU|S_IRWXG);
		if (jpg_fd < 0) {
			perror("create");
			return -1;
		}






	//pgm2jpg
	JSAMPROW row_pointer[1];  /* pointer to JSAMPLE row[s] */
	int row_stride; 	  /* physical row width in image buffer */

	jpeg_mem_dest(&cinfo, &jpg_data, &jpg_size);
	cinfo.image_width = pgms.width;	  /* image width and height, in pixels */
	cinfo.image_height = pgms.height;
	cinfo.input_components = 1; 	  /* # of color components per pixel */
	cinfo.in_color_space = JCS_GRAYSCALE;	  /* colorspace of input image */
	jpeg_set_defaults(&cinfo);
	jpeg_set_quality(&cinfo, 50, TRUE /* limit to baseline-JPEG values */);
	
	
	jpeg_start_compress(&cinfo, TRUE);
	row_stride = pgms.width;   /* JSAMPLEs per row in image_buffer */
	while (cinfo.next_scanline < cinfo.image_height) {
	  row_pointer[0] = &pgms.data[cinfo.next_scanline * row_stride];
	  (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}
	
	jpeg_finish_compress(&cinfo);








		//save jpeg file
		printf("jpg size:%lu\n", jpg_size);
		ret = write(jpg_fd, jpg_data, jpg_size);

		close(pgm_fd);
		close(jpg_fd);
		
	}


	//~pgm_parse
	jpeg_destroy_compress(&cinfo);

	free(jpg_data);

	return 0;
}



