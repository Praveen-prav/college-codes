/*
Name : M Praveen
Roll No :  CS20B1023
*/

#include <stdio.h>
#include <stdlib.h>

char data[4], sent_data[7], hamming[3], received_data[7];
int parity_bits[3], parity = 0, i, error_bit;

void print_data()
{
    printf("Number of parity bits : %d\n", 3);
    printf("Input data = ");
    for (i = 0; i < 4; i++)
    {
        printf("%c", data[i]);
    }
    printf("\nHamming Code = %s\n", hamming);
    printf("Sent data = %s\n\n", sent_data);
}

void gen_hcode()
{
    int l;

    // Filling the data in the hamming code
    sent_data[2] = data[0];
    sent_data[4] = data[1];
    sent_data[5] = data[2];
    sent_data[6] = data[3];

    // For parity bit 1
    l = 0;
    if (sent_data[2] == '1')
        l++;
    if (sent_data[4] == '1')
        l++;
    if (sent_data[6] == '1')
        l++;
    if (parity == 1)
    {
        if (l % 2 == 0)
        {
            sent_data[0] = '1';
            hamming[0] = '1';
        }
        else
        {
            sent_data[0] = '0';
            hamming[0] = '0';
        }
    }
    else
    {
        if (l % 2 == 1)
        {
            sent_data[0] = '1';
            hamming[0] = '1';
        }
        else
        {
            sent_data[0] = '0';
            hamming[0] = '0';
        }
    }

    // For parity bit 2
    l = 0;
    if (sent_data[2] == '1')
        l++;
    if (sent_data[5] == '1')
        l++;
    if (sent_data[6] == '1')
        l++;
    if (parity == 1)
    {
        if (l % 2 == 0)
        {
            sent_data[1] = '1';
            hamming[1] = '1';
        }
        else
        {
            sent_data[1] = '0';
            hamming[1] = '0';
        }
    }
    else
    {
        if (l % 2 == 1)
        {
            sent_data[1] = '1';
            hamming[1] = '1';
        }
        else
        {
            sent_data[1] = '0';
            hamming[1] = '0';
        }
    }

    // For parity bit 3
    l = 0;
    if (sent_data[4] == '1')
        l++;
    if (sent_data[5] == '1')
        l++;
    if (sent_data[6] == '1')
        l++;
    if (parity == 1)
    {
        if (l % 2 == 0)
        {
            sent_data[3] = '1';
            hamming[2] = '1';
        }
        else
        {
            sent_data[3] = '0';
            hamming[2] = '0';
        }
    }
    else
    {
        if (l % 2 == 1)
        {
            sent_data[3] = '1';
            hamming[2] = '1';
        }
        else
        {
            sent_data[3] = '0';
            hamming[2] = '0';
        }
    }
}

void detect_hcode()
{
    int l;

    // For parity bit 1
    l = 0;
    if (received_data[0] == '1')
        l++;
    if (received_data[2] == '1')
        l++;
    if (received_data[4] == '1')
        l++;
    if (received_data[6] == '1')
        l++;
    if (parity == 1)
    {
        if (l % 2 == 1)
        {
            parity_bits[0] = 0;
        }
        else
        {
            parity_bits[0] = 1;
        }
    }
    else
    {
        if (l % 2 == 0)
        {
            parity_bits[0] = 0;
        }
        else
        {
            parity_bits[0] = 1;
        }
    }

    // For parity bit 2
    l = 0;
    if (received_data[1] == '1')
        l++;
    if (received_data[2] == '1')
        l++;
    if (received_data[5] == '1')
        l++;
    if (received_data[6] == '1')
        l++;
    if (parity == 1)
    {
        if (l % 2 == 1)
        {
            parity_bits[1] = 0;
        }
        else
        {
            parity_bits[1] = 1;
        }
    }
    else
    {
        if (l % 2 == 0)
        {
            parity_bits[1] = 0;
        }
        else
        {
            parity_bits[1] = 1;
        }
    }

    // For parity bit 2
    l = 0;
    if (received_data[3] == '1')
        l++;
    if (received_data[4] == '1')
        l++;
    if (received_data[5] == '1')
        l++;
    if (received_data[6] == '1')
        l++;
    if (parity == 1)
    {
        if (l % 2 == 1)
        {
            parity_bits[2] = 0;
        }
        else
        {
            parity_bits[2] = 1;
        }
    }
    else
    {
        if (l % 2 == 0)
        {
            parity_bits[2] = 0;
        }
        else
        {
            parity_bits[2] = 1;
        }
    }

    error_bit = (4 * parity_bits[2]) + (2 * parity_bits[1]) + (1 * parity_bits[0]);

    printf("\n\nReceived Message = %s\n", received_data);
    printf("Error Result: ");
    printf("Error is in the %dth bit.\n", error_bit);
    printf("Parity Bits Code: ");
    for (i = 0; i < 3; i++)
    {
        printf("%d", parity_bits[i]);
    }
    printf("\n");
}

void copyOriginal()
{
    for (i = 0; i < 7; i++)
    {
        received_data[i] = sent_data[i];
    }
}

int main()
{
    int choice = 0;
    printf("Enter the message without spaces upto 4 bits : ");
    scanf("%s", data);
    while (1)
    {
        printf("Select parity\n");
        printf("1. odd parity\n2. even parity\n");
        printf("Enter your option : ");
        scanf("%d", &parity);

        if (parity == 1)
            break;
        else if (parity == 2)
            break;
        else
            continue;
    }
    while (1)
    {
        printf("\n1. No Error: without changing data and redundant bits check for error.\n");
        printf("2. Error 1: change one random data bit and check for errors.\n");
        printf("3. Error 2: change one random parity bit and check for errors.\n");
        printf("4. Error 3: change one random data and one parity bit and check for errors.\n");
        printf("5. Exit.\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            gen_hcode();
            print_data();
        }
        break;
        case 2:
        {
            gen_hcode();
            copyOriginal();
            // Changing 4th data bit

            if (received_data[6] == '1')
                received_data[6] = '0';
            else
                received_data[6] = '1';

            // Detecting the error
            detect_hcode();
        }
        break;
        case 3:
        {
            gen_hcode();
            copyOriginal();
            // Changing 1st parity bit
            if (received_data[0] == '1')
                received_data[0] = '0';
            else
                received_data[0] = '1';

            // Detecting the error
            detect_hcode();
        }
        break;
        case 4:
        {
            gen_hcode();
            copyOriginal();
            // Changing 1st parity bit
            if (received_data[0] == '1')
                received_data[0] = '0';
            else
                received_data[0] = '1';

            // Changing 4th data bit
            if (received_data[6] == '1')
                received_data[6] = '0';
            else
                received_data[6] = '1';

            // Detecting the error
            detect_hcode();
            printf("\nhamming code can only detect one bit errors. so it can be right or wrong\n\n");
        }
        break;
        case 5:
        {
            exit(0);
        }
        break;
        default:
        {
            printf("Please Enter the Correct Choice.\n");
        }
        break;
        }
    }
    return 0;
}