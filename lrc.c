// Name     : M Praveen
// Roll No  : cs20b1023

// Lab Assignment 1


#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000

void LRC();

int data[SIZE], data_size, lrc[SIZE], lrc_size, temp[SIZE], temp_size, parity[SIZE];
int i, j;

int main()
{
    int option;
    while(1)
    {
        printf("\n\n1. Send a message.");
        printf("\n2. Check received message.");
        printf("\n3. Exit\n");
        printf("\nEnter your option : ");
        scanf("%d", &option);

        switch(option)
        {
            case 1:
                printf("Enter the size of the bits : ");
                scanf("%d", &data_size);

                printf("Enter the  bits : ");
                for(i = 0; i < data_size; i++)
                {
                    scanf("%d", &data[i]);
                }

                int blocks = data_size/4;

                for(i = 0; i < blocks; i++)
                {
                    int count = 0;
                    for(j = 4*i; j < 4*(i+1); j++)
                    {
                        if(data[j] == 1)
                        {
                            count++;
                        }
                    }

                    if(count % 2 == 1)
                    {
                        parity[i] = 1;
                    }
                    else
                    {
                        parity[i] = 0;
                    }
                }

                int data_parity_size = blocks + data_size;

                for(i = 0; i < data_size; i++)
                {
                    temp[i] = data[i];
                }

                for(i = 0; i < blocks; i++)
                {
                    temp[i + data_size] = parity[i];
                }

                for(i = 0; i < data_parity_size; i++)
                {
                    printf("%d ", temp[i]);
                }

                break;

            case 2:


                break;

            case 3:
                exit(0);
                break;

            default:
                printf("\nEnter a correct option.\n");
        }
    }
    return 0;
}