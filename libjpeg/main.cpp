
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "pgm.h"

char *pgmfile[] = {
	"0a6e77bc-bb48-4286-b054-b0ffa0ccc82d.pgm",
	"0d300776-6deb-44d4-856c-22ef93757e71.pgm",
	"0de6aa5c-d0e6-4f6c-bf8d-72fb11bb3c73.pgm",
	"0f3b0da3-2e9b-4920-94f1-2a77a619fab7.pgm",
	"1a2319b3-4da9-484f-a893-29063e183d93.pgm",
	"1addb643-735e-4341-966d-0383abfcdb5f.pgm",
	"1b61d6e6-a45e-466f-aa0f-7d9264d279cb.pgm",
	"1cdc6b8b-284c-41d7-bb87-f371a8bb97bd.pgm",
	"1fba0819-2c29-4747-b3db-195c96994817.pgm",
	"2a4a5c0d-45b4-4150-bfa0-27266a7eb0f9.pgm",

};

int main(int argc, char *argv[])
{
	
	pgm_parse pgm;
	char *pgm_data;
	char *jpg_data;
	char *apenfix;
	int ret;
	int pgm_fd;
	int jpg_fd;
	long unsigned int jpg_size;
	int pgm_size;
	char target_filename[100];
	
	pgm_data = (char *)malloc(1*1000*1000);
	jpg_data = (char *)malloc(1*1000*1000);

	
	int i;
	for (i = 0; i < sizeof(pgmfile)/sizeof(pgmfile[0]); i++) {
		pgm_fd = open(pgmfile[i], O_RDONLY);
		if (pgm_fd < 0) {
			perror("open");
			return -1;
		}

		memset(target_filename, 0, 100);
		strcpy(target_filename, pgmfile[i]);
		apenfix = strstr(target_filename, ".pgm");
		memcpy(apenfix, ".jpg", 4);
		jpg_fd = open(target_filename, O_RDWR|O_CREAT, S_IRWXU|S_IRWXG);
		if (jpg_fd < 0) {
			perror("create");
			return -1;
		}

		pgm_size = read(pgm_fd, pgm_data, 1*1000*1000);
		printf("pgm size:%d\n", pgm_size);

		jpg_size = 1*1000*1000;//alloc enough mem
		//pgm.pgm2jpg(pgm_data, &jpg_data, &jpg_size, 50);
		printf("jpg size:%lu\n", jpg_size);
		ret = write(jpg_fd, jpg_data, jpg_size);

		close(pgm_fd);
		close(jpg_fd);
		
	}

	free(pgm_data);
	free(jpg_data);

	return 0;
}
