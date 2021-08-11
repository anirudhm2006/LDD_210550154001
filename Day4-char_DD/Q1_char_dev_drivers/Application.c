#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
	int FileDesc;
	//char Ubuff[]="This is user buffer..sending data to the kernel....";
	//char Kbuff[100];
	FileDesc=open("/dev/MyCharDevice",O_RDWR,0777);
	if(FileDesc < 0)
	{
		printf("\n Error opening device\n");
		exit(1);
	}
	printf("\n closing\n");
	close(FileDesc);
}

