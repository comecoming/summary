#ifndef __PGM_H__
#define __PGM_H__

#include "jpeglib.h"

enum pgm_type {
	TYPE_P2,
	TYPE_P5,

};

class pgm_parse {
public:
	pgm_parse();
	~pgm_parse();
	int pgm2jpg(char *pgm_data, int width, int height, int quality, char **jpg_data, long unsigned int *jpg_size);

private:
	char* raw_data;
	char* jpeg_data;
	int raw_data_size;
	int pgm_fd;
	//int pgm_high;
	//int pgm_width;
	int max_val;
	pgm_type type;
	int data_offset;

	
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;
};


#endif
