#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/io.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#define OPEN_ERROR -1
int main(int argc, char **argv){
    if(argc!=3){
      printf("Usage: %s [file 1] [file 2]\n",argv[0]);
      return EXIT_FAILURE;
    }
    int fd1=open(argv[1],O_RDONLY);
    int fd2=open(argv[2],O_RDONLY);
    if(fd1==OPEN_ERROR||fd2==OPEN_ERROR){
        perror("[open]");
        return EXIT_FAILURE;
    }
    struct stat s1,s2;
    if(fstat(fd1,&s1)==-1||fstat(fd2,&s2)==-1){
      perror("[fstat]");
      close(fd1);
      close(fd2);
      return EXIT_FAILURE;
    }
    printf("%s\n",strcmp((char*)mmap(NULL,s1.st_size,PROT_READ,MAP_PRIVATE,fd1,0),(char*)mmap(NULL,s2.st_size,PROT_READ,MAP_PRIVATE,fd2,0))==0?"No difference was found.":"The files are different.");
    close(fd1);
    close(fd2);
    return EXIT_SUCCESS;
}
