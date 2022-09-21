/*
Name : M Praveen
Roll No : cs20b1023
Lab - 5
Q) Implementing Go back N 
*/

#include <stdio.h>

#define SIZE 1000

int frameSize, windowSize, totalFrames = 0, drop;
int arr[SIZE];

void goBackN()
{
    int i;
    for(i = 1; i <= frameSize; i++)
    {
        if(totalFrames - i < windowSize - 1)
        {
            if((totalFrames + 1) % drop == 0)
            {
                totalFrames += frameSize - i + 1;
                printf("\nNot Received frame - %d\n", i - 1);
                printf("Resending the frames....\n\n");
            }

            else
            {
                totalFrames++;
                printf("Received frame - %d\n", i - 1);
            }
        }

        else
        {
            if((totalFrames + 1) % drop == 0)
            {
                totalFrames += windowSize;
                printf("\nNot Received frame - %d\n", i - 1);
                printf("Resending the frames....\n\n");
            }

            else
            {
                totalFrames++;
                printf("Received frame - %d\n", i - 1);
            }
        }
        
    }
}

int main()
{
    printf("Enter size of the window : ");
    scanf("%d", &windowSize);

    printf("Enter the number of frames : ");
    scanf("%d", &frameSize);

    printf("Enter the number of the frame to drop : ");
    scanf("%d", &drop);

    printf("Enter the frames : ");
    for(int i = 0; i < frameSize; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("\n");
    goBackN();

    printf("\n\nTotal no.of frames is : %d\n", totalFrames);
    return 0;
}