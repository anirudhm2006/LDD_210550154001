#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
	int fd;
	char write_buf[] = "Embedded Systems";
	char read_buf[100] = "\0";
	fd = open("/dev/sample_cdev",O_RDWR,0777);
	if(fd < 0)
	{
		printf("Unable to open the file\n");
		return (-1);
	}
	

	if(fork() == 0)
	{
		//writing the value to the device
		write(fd,write_buf, sizeof(write_buf));
	}
	else
	{
		//reading the value from the device
		read(fd, read_buf, sizeof(read_buf));
		printf("value read : %s\n",read_buf);
		wait(NULL);
	}
	close(fd);
	return 0;
	
}
