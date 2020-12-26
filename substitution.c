#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main(int argc, string argv[])
{
    //reject if not given 2 command line arguments
    if (argc != 2)
    {
        printf("Error. Input 26 character key\n");
        return 1;
    }
    //reject if not 26 letters long
    if (strlen(argv[1]) != 26)
    {
        printf("Error. Input 26 character key.\n");
        return 1;
    }
    string alpha = argv[1];
    //reject if each character is not a letter
    for (int i = 0; i < strlen(alpha); i++)
    {
        if (isalpha(alpha[i]) == 0)
        {
            printf("Error. Input alphabetical key only.\n");
            return 1;
        }
    }
    //convert key to numbers 1-26
    int key[strlen(alpha)];
    int sum = 0;
    for (int i = 0; i < strlen(alpha); i++)
    {
        if (alpha[i] < 91)
        {
            key[i] = (alpha[i] + 32);
        }
        else
        {
            key[i] = alpha [i];
        }
        sum = sum + key[i];
    }
    //check if each letter used only once, use "sum" from above
    if (sum != 2847)
    {
        printf("Error. Each letter should be used only once.\n");
        return 1;
    }
    //get plaintext message from user
    string plaintext = get_string("plaintext:");
    printf("ciphertext: ");
    
    //convert string input via key
    int crypt[strlen(plaintext)];
    for (int i = 0; i < strlen(plaintext); i++)
    {   
        //preserve punctuation, spaces, etc.
        if (plaintext[i] < 65 && plaintext [i] > 31)
        {
            crypt[i] = plaintext [i];
        }
        //preserve capitalizations
        else if (plaintext [i] < 91 && plaintext [i] > 64)
        {
            crypt[i] = toupper(key[plaintext[i] - 65]);
            
        }
        else
        {
            crypt[i] = key[plaintext[i] - 97];
        }
        //print result in letters
        printf("%c", (char)crypt[i]);
    }
        printf("\n");
        return 0;
}