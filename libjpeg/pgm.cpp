#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "pgm.h"


pgm_parse::pgm_parse()
{
	raw_data_size = 320*240;
	raw_data = (unsigned char *)malloc(320*240);

}

pgm_parse::~pgm_parse()
{

	if (raw_data) {
		free(raw_data);
		raw_data = NULL;
	}

}

struct pgm_entity pgm_parse::parse(char *file_name)
{
	int ret;
	char buf[100];
	int data_offset;
	char *pos;
	char* _pos;
	struct pgm_entity entity;
	int pgm_size;

	int fd = open(file_name, O_RDONLY);

	read(fd, buf, 100);
	_pos = buf;
	pos = buf;
	
	while (1) {
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
		return entity;
	}
	
	while (1) {
		pos = strchr(pos, '\n');
		pos++;
		if (*pos != '#')
			break;
	}
	sscanf(pos, "%d %d", &entity.width, &entity.height);

	while (1) {
		pos = strchr(pos, '\n');
		pos++;
		if (*pos != '#')
			break;
	}
	sscanf(pos, "%d", &pgm_size);
	
	while (1) {
		pos = strchr(pos, '\n');
		pos++;
		if (*pos != '#')
			break;
	}

	data_offset = pos - _pos;
	
	printf("%dx%d %d %d\n", entity.width, entity.height, pgm_size, data_offset);

	lseek(fd, data_offset, SEEK_SET);

	pgm_size = entity.width*entity.height;
	if (raw_data_size < pgm_size) {
		raw_data = (unsigned char *)realloc(raw_data, pgm_size);
		raw_data_size = pgm_size; 
	}
	read(fd, raw_data, pgm_size);
	entity.data = raw_data;

	close(fd);

	return entity;
}


