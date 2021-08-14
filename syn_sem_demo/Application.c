#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
  int fd, var1,var2;
  fd = open("/dev/my_sample_cdev",O_RDONLY,0777);
  
  if(fd<0)
  {
    printf("Unable to open file\n");
    exit(0);
  }
  
  if(fork()==0)
  {
    read(fd,&var1,sizeof(var1));
    printf("Read first value: %d\n",var1);
    exit(0);
  }
  else 
  {
    read(fd,&var2,sizeof(var2));
    printf("Read first value: %d\n",var2);
    wait(NULL);
  }
  close(fd);
  return 0;
}
