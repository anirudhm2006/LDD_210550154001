#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "ioctl.h"

int main()
{
	int FileDesc;
	int oper,n1,n2,output;
	char ubuf[]="This is user buffer..sending data to the kernel....";
	char kbuf[100];
	FileDesc=open("/dev/MyCharDevice",O_RDWR,0777);
	if(FileDesc < 0)
	{
		printf("Error in opening device.\n");
		return 0;
	}
	
	printf("operation\n");
	printf("1.Addition \n 2.Subtraction\n 3.Multiplication\n 4. Division\n");
	scanf("%d",&oper);
	printf("writing data to the driver\n");
	ioctl(FileDesc,operator,(int*)&oper);
	
	printf("Enter the value of n1\n");
	scanf("%d",&n1);
	
	printf("Enter the value of n2\n");
	scanf("%d",&n2);
	
	ioctl(FileDesc,num1,(int*) &n1);
	ioctl(FileDesc,num2,(int*) &n2);
	
	printf("Reading data from driver\n");
	ioctl(FileDesc,Read_data, (int*) &output);
	printf("output is : %d\n",output);
	
	write(FileDesc,ubuf,sizeof(ubuf));
	read(FileDesc,kbuf,50);
	printf("closing driver\n");
	close(FileDesc);
}
	

