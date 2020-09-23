#ifndef __PGM_H__
#define __PGM_H__


enum pgm_type {
	TYPE_P2,
	TYPE_P5,

};

struct pgm_entity {
	int width;
	int height;
	unsigned char *data;
};

class pgm_parse {
public:
	pgm_parse();
	~pgm_parse();
	struct pgm_entity parse(char *file_name);

private:
	unsigned char* raw_data;
	char* jpeg_data;
	int raw_data_size;
	int pgm_fd;
	pgm_type type;
	int data_offset;

};


#endif
