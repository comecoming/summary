#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>

int main(int argc, char *argv[])
{
	int fd = open(argv[1], O_RDWR);

	Elf64_Ehdr elfhead;
	read(fd, &elfhead, sizeof(elfhead));

	Elf64_Shdr elfsection;
	lseek(fd, 0, SEEK_CUR);
	read(fd, &elfsection, sizeof(elfsection));

	Elf64_Sym elfsymbol;
	lseek(fd, 0, SEEK_CUR);
	for (;;) {
		read(fd, &elfsymbol, sizeof(elfsymbol));
	}

	close(fd);

	return 0;
}
