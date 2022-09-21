/*
Name : M Praveen
Roll No : cs20b1023
lab 6 - checksum
*/

#include <stdio.h>
#define SIZE 72
#define buff 100

int binString[SIZE + 4];
char string[9];

void checkSum(int a[], int n);
int parity(int a[], int n);

int strToBin();

int main()
{
    printf("Enter your roll number for sender : ");
    for (int i = 0; i < 9; i++)
    {
        scanf("%c", &string[i]);
    }

    strToBin();
    checkSum(binString, SIZE + 4);

    printf("--------------------------------------Data sent--------------------------------------\n");
    for (int i = 0; i < SIZE; i++)
    {
        if (i % 8 == 0)
            printf("\n");
        printf("%d", binString[i]);
    }

    printf("\n");

    printf("Check Sum parity bits at sender side: ");
    
    for (int i = SIZE; i < SIZE + 4; i++)
    {  
        printf("%d", binString[i]);
    }
        

    // if(binString[SIZE+3]){

    //     binString[SIZE+3]=0;
    // }
    // else{
    //     binString[SIZE+3]=1;
    // }

    int c = parity(binString, SIZE + 4);
    if (c == 1)
    {
        printf("\n--------------------------------------Received parityBits is correct--------------------------------------\n");
        for (int i = 0; i < SIZE; i++)
        {
            if (i % 8 == 0)
                printf("\n");
            printf("%d", binString[i]);
        }
        printf("\n");

        printf("Check Sum parity bits : ");
        for (int i = SIZE; i < SIZE + 4; i++)
        {
            printf("%d", binString[i]);
        }

        printf("\n");
    }

    else
    {
        printf("Data is wrong");
    }

    return 0;
}

int strToBin()
{
    for (int i = 0; i < SIZE + 4; i++)
        binString[i] = 0;

    int j = 0, r = 0;
    for (int i = 0; i < SIZE; i += 8)
    {
        char c = string[j]; 
        int a = c;          
        int ch[8];
        for (int m = 0; m < 8; m++)
            ch[m] = 0;

        int z = 0;
        while (a > 0)
        {
            int res = a % 2;
            ch[z] = res;
            a /= 2;
            z++;
        }

        for (int i = 7; i >= 0; i--)
        {
            binString[r] = ch[i];
            r++;
        }

        j++;
    }
}

    void checkSum(int a[], int n)
{
    int res[4] = {0, 0, 0, 0};

    for (int i = 0; i < n; i = i + 4)
    {
        int tempBit = 0, j = 4;
        while (j--)
        {
            res[j] = tempBit + res[j] + a[i + j];

            if ((res[j] == 1) || (res[j] == 0))
            {
                tempBit = 0;
                continue;
            }
            if (res[j] == 2)
            {
                tempBit = 1;
                res[j] = 0;
            }
            if (res[j] == 3)
            {
                tempBit = 1;
                res[j] = 1;
            }
        }
        if (tempBit == 1)
        {
            if (res[3] == 0)
            {
                res[3] = 1;
            }
            else if (res[2] == 0)
            {
                res[2] = 1;
            }
            else if (res[1] == 0)
            {
                res[1] = 1;
            }
            else
            {
                res[0] = 1;
            }
        }
    }
    for (int i = 0; i < 4; i++)
    {
        if (res[i] == 0)
            a[n - 4 + i] = 1;
        else
            a[n - 4 + i] = 0;
    }
}

int parity(int a[], int n)
{
    int parityBits[4] = {0, 0, 0, 0};

    for (int i = 0; i < n; i = i + 4)
    {
        int tempBit = 0, j = 4;
        while (j--)
        {
            parityBits[j] = tempBit + parityBits[j] + a[i + j];

            if ((parityBits[j] == 1) || (parityBits[j] == 0))
            {
                tempBit = 0;
                continue;
            }
            if (parityBits[j] == 2)
            {
                tempBit = 1;
                parityBits[j] = 0;
            }
            if (parityBits[j] == 3)
            {
                tempBit = 1;
                parityBits[j] = 1;
            }
        }
        if (tempBit == 1)
        {
            if (parityBits[3] == 0)
            {
                parityBits[3] = 1;
            }
            else if (parityBits[2] == 0)
            {
                parityBits[2] = 1;
            }
            else if (parityBits[1] == 0)
            {
                parityBits[1] = 1;
            }
            else
            {
                parityBits[0] = 1;
            }
        }
    }

    for (int i = 0; i < 4; i++)
    {
        if (parityBits[i] == 0)
            a[n - 4 + i] = 1;
        else
            a[n - 4 + i] = 0;

        if (!parityBits[i])
        {
            return 0;
        }
    }
    return 1;
}