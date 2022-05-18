//program to find the greatest number in an array of 10 integers
#include<stdio.h>
#include<unistd.h>

int main()
{
    int fd[2],fd1[2];
    int my_array[10], max;
    int pipe_status;
    int rmax[1];

    pipe_status = pipe(fd);
    pipe_status = pipe(fd1);

    printf("Input Values\n");
    for(int i = 0;i < 10; i++)
    {
        printf("Number %d: ", i + 1);
        scanf("%d", &my_array[i]);
    }

    if(pipe_status < 0)
    {
        printf("Pipe cannot be created\n");
        return -1;
    }

    if(fork() == 0)
    {
        printf("Child process for reading\n");
        printf("Child process ID: %d\n", getpid());
        printf("    \n");
        read(fd[0], my_array, sizeof(my_array));
        max = my_array[0];
        for(int i = 1;i < 10;i++)
        {
            if(my_array[i] > max)
            {
                max = my_array[i];
            }
        }
        rmax[0] = max;
        write(fd1[1], rmax, sizeof(rmax));
    }
    else
    {
        printf("Parent process for writing\n");
        printf("Parent process ID: %d\n", getpid());
        printf("    \n");
        write(fd[1], my_array, sizeof(my_array));
        read(fd1[0], rmax, sizeof(rmax));
        printf("Highest Number: %d\n", rmax[0]);
    }
    return 0;
}
