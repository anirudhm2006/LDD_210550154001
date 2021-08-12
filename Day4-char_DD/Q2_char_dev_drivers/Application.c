#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int FileDesc;
	char ubuf[]="This is user buffer..sending data to the kernel....";
	char kbuf[100];
	FileDesc=open("/dev/MyCharDevice",O_RDWR,0777);
	if(FileDesc < 0)
	{
		printf("\n Error opening device\n");
		exit(1);
	}
	write(FileDesc,ubuf,sizeof(ubuf));
	read(FileDesc,kbuf,50);
	printf("The data read from the Kernel is\n %s \n",kbuf);
	printf("\n closing\n");
	close(FileDesc);
}

