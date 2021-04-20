#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int fd, val, i;
	fd = open("/dev/joypad", O_RDONLY);
	while(1)
	{
		val = read(fd, 0, 0);
		for(i=0; i<8; i++)
		{
			printf("%d%d ", i, (val & 1<<i) ? 1 : 0);
		}
		printf("\r\n");
	}
	close(fd);
	return 0;
}
