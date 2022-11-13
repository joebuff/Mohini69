#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
    printf("PID of ex1.c=%d\n",getpid());
    char *args[]={"Hello","Manish","Sarmah",NULL};
    execv("%ex2",args);
    printf("Back to ex1.c");
    return 0;
}