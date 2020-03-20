#include <stdio.h>
#include <string.h>

#include "pgm.h"


pgm_parse::pgm_parse()
{
	pgm_fd = -1;
	raw_data = NULL;
	raw_data_size = 0;

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);

	
}

pgm_parse::~pgm_parse()
{
	jpeg_destroy_compress(&cinfo);

}

/*
pgm_data:原始点数据
width:
height:
quality:压缩质量（0-100）

jpg_data:压缩数据缓存
jpg_size:压缩数据大小
*/
int pgm_parse::pgm2jpg(char *pgm_data, int width, int height, int quality, char **jpg_data, long unsigned int *jpg_size)
{
	int ret;
	char *pos;
	unsigned char* _pos;
	
	JSAMPROW row_pointer[1];  /* pointer to JSAMPLE row[s] */
	int row_stride; 	  /* physical row width in image buffer */

	if (jpg_data == NULL || *jpg_data == NULL || *jpg_size == 0) {
		printf("no initial buffer\n");
		return -1;
	}
	
	pos = pgm_data;

	/*while (1) {
		if (*pos != '#')
			break;
		pos = strchr(pos, '\n');
		pos++;
	}
	if (strncmp(pos, "P5", 2) == 0) {
		type = TYPE_P5;
	} else if (strncmp(pos, "P2", 2) == 0) {
		type = TYPE_P2;
	} else {
		printf("format not support\n");
		return -1;
	}
	
	while (1) {
		pos = strchr(pos, '\n');
		pos++;
		if (*pos != '#')
			break;
	}
	sscanf(pos, "%d %d", &pgm_width, &pgm_high);

	while (1) {
		pos = strchr(pos, '\n');
		pos++;
		if (*pos != '#')
			break;
	}
	sscanf(pos, "%d", &max_val);
	
	while (1) {
		pos = strchr(pos, '\n');
		pos++;
		if (*pos != '#')
			break;
	}

	data_offset = pos - pgm_data;*/
	
	//printf("%dx%d %d %d\n", pgm_width, pgm_high, max_val, data_offset);

	jpeg_mem_dest(&cinfo, (unsigned char **)jpg_data, jpg_size);
	cinfo.image_width = width;	  /* image width and height, in pixels */
	cinfo.image_height = height;
	cinfo.input_components = 1; 	  /* # of color components per pixel */
	cinfo.in_color_space = JCS_GRAYSCALE;	  /* colorspace of input image */
	jpeg_set_defaults(&cinfo);
	jpeg_set_quality(&cinfo, quality, TRUE /* limit to baseline-JPEG values */);
	
	
	jpeg_start_compress(&cinfo, TRUE);
	row_stride = width;   /* JSAMPLEs per row in image_buffer */
	_pos = (unsigned char *)pos;
	while (cinfo.next_scanline < cinfo.image_height) {
	  row_pointer[0] = &_pos[cinfo.next_scanline * row_stride];
	  (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}
	
	jpeg_finish_compress(&cinfo);

	return 0;
	
}

