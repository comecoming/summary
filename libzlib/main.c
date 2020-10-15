#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <zlib.h>

int main(int argc, char *argv[])
{
	char *a = malloc(1024*10);
	char *b = malloc(1024*10);
	unsigned long len = 1024*10;
	int ret;

	int fd = open(argv[1], O_RDONLY);
	ret = read(fd, b, 1024*10);
	printf("read %d\n", ret);

	compress(a, &len, b, 1024*10);
	printf("zip %lu\n", len);

	close(fd);






	return 0;
}
