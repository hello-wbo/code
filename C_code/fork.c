//此代码只能用在linux系统中
#include <sys/unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])  {
    int i,j,status;
    int pid[3];

    for(i=0; i<3;i++){
        if((pid[i]=fork()) >0){

            printf("This is child process pid=%d\n",pid[i]);

        } else{
            printf("This is father process pid=%d\n",pid[i]);
            exit( EXIT_SUCCESS);
        }

    }

    return EXIT_SUCCESS;
}
