// Name     : M Praveen
// Roll No  : cs20b1023

// Lab Assignment 1

#include <stdio.h>
#include <stdlib.h>
#define SIZE 1000

void division();
void check_corruption();

int data[SIZE], poly[SIZE];
int  data_size, poly_size, i, j;
int temp[SIZE], temp_size, final[SIZE];

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
                printf("\nEnter the size of the data bits : ");
                scanf("%d", &data_size);

                printf("Enter the data bits : ");
                for(i = 0; i < data_size; i++)
                {
                    scanf("%d", &data[i]);
                }

                printf("\nEnter the size of the polynomial bits : ");
                scanf("%d", &poly_size);

                printf("Enter the polynomial bits : ");
                for(i = 0; i < poly_size; i++)
                {
                    scanf("%d", &poly[i]);
                }

                temp_size = data_size + (poly_size - 1);

                for(i = 0; i < temp_size; i++)
                {
                    temp[i] = 0;
                }

                for(i = 0; i < data_size; i++)
                {
                    temp[i] = data[i];
                    final[i] = data[i];
                }
                
                division();

                for(i = 0; i < poly_size; i++)
                {
                    final[i + data_size] = data[i];
                }
                printf("\n\nSender data is : ");
                for(i = 0; i < temp_size; i++){
                    printf("%d ", final[i]);
                }

                break;

            case 2:

                printf("\nEnter the size of the data bits : ");
                scanf("%d", &temp_size);

                printf("Enter receiver data : ");
                for(i = 0; i < temp_size; i++)
                    scanf("%d", &temp[i]);

                printf("\nEnter the size of the polynomial bits : ");
                scanf("%d", &poly_size);

                printf("Enter the polynomial bits : ");
                for(i = 0; i < poly_size; i++)
                {
                    scanf("%d", &poly[i]);
                }

                division();

                for(i = 0; i < poly_size; i++)
                {
                    final[i + data_size] = data[i];
                }
                printf("\n\nReceiver data is : ");
                for(i = 0; i < temp_size; i++){
                    printf("%d ", final[i]);
                }

                check_corruption();

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

void division()
{
    for( j = 0; j < poly_size; j++)
    {
        data[j] = temp[j];
    }

    while(j <= temp_size)
    {
        if(data[0] == 1)
            for(i = 1; i < poly_size; i++)
            {
                if(data[i] == poly[i])
                {
                    data[i] = 0;
                }
                else
                    data[i] = 1;
            }

        for(i = 0; i < poly_size - 1; i++)
            data[i] = data[i + 1];

        data[i] = temp[j++];
    }
}

void check_corruption(){
    int flag = 0;
    for(i = 0; i < poly_size - 1; i++)
    {
        if(data[i] == 1)
        {
            flag = 1;
            break;
        }
    }

    if(flag == 0)
       printf("\nData transmitted is not corrupted\n");

    else   
         printf("\nData transmitted is corrupted\n");
}