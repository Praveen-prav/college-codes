#include <stdio.h>
#include <unistd.h>

int main()
{
    int a = fork();

    if (a == 0)
    {
        printf("Child - 1\n");
        printf("PID of child 1 : %d\n", getpid());
        printf("PID of parent : %d\n", getppid());

        a = fork();
        if (a == 0)
        {
            printf("Child - 2\n");
            printf("PID of child 2 : %d\n", getpid());
            printf("PID of parent : %d\n", getppid());

            a = fork();
            if (a == 0)
            {
                printf("Child - 3\n");
                printf("PID of child 3 : %d\n", getpid());
                printf("PID of parent : %d\n", getppid());

                a = fork();
                if (a == 0)
                {
                    printf("Child - 4\n");
                    printf("PID of child 4 : %d\n", getpid());
                    printf("PID of parent : %d\n", getppid());
                }
            }
        }
    }

    printf("parent\n");
    printf("PID of parent : %d\n", getppid());
    return 0;
}