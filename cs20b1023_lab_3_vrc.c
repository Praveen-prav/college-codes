// Name     : M Praveen
// Roll No  : cs20b1023

// Lab Assignment 1


#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000

int data[SIZE], data_size, temp[SIZE], parity[SIZE];
int i, j, blocks, flag = 0;

void VRC()
{
    blocks = data_size/4;

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
}

void verify()
{
    for(i = 0; i < data_size; i++)
    {
        if(data[i] != temp[i])
        {
            flag = 1;
            break;
        }

        else
            flag = 0;
    }
}

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
                printf("Enter the size of the bits in the multiples of 4 : ");
                scanf("%d", &data_size);

                if(data_size % 4 != 0)
                {
                    printf("\nPlease enter the size of the bits in multiples of 4\n");
                    break;
                }

                printf("Enter the  bits : ");
                for(i = 0; i < data_size; i++)
                {
                    scanf("%d", &data[i]);
                }

                VRC();

                for(i = 0; i < data_size; i++)
                {
                    temp[i] = data[i];
                }



                for(i = 0; i < blocks; i++)
                {
                    temp[i + data_size] = parity[i];
                }

                for(i = 0; i < data_size + blocks; i++)
                {
                    printf("%d ", temp[i]);
                }


                break;

            case 2:
                
                printf("Enter the size of the bits (data bits + VRC code bits): ");
                scanf("%d", &data_size);

                printf("Enter the  bits : ");
                for(i = 0; i < data_size; i++)
                {
                    scanf("%d", &data[i]);
                }
                
                verify();

                if(flag == 0)
                    printf("\nData transmitted is not corrupted - \033[1;32mACCEPTED\033[0m\n");

                else
                    printf("\nData transmitted is corrupted - \033[1;31mREJECTED\033[0m\n");
                
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
