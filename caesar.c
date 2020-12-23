#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


int main(int argc, string argv[])
{   
    //reject incorrect number of command line arguments
    if (argc != 2)
    {
        printf("error, input single integer please\n");
        return 1;
    }
    
     //reject nondigit
    string initialkey = argv[1]; 
    int a = 1;
    for (int i = 0; i <strlen(initialkey); i++)
    {
        a = isdigit(initialkey[i]); 
        if (a == 0)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    
    //reject non-negative digit
    int key = atoi(argv[1]);
    if (key < 0)
    {
        printf("error, input positive integer please\n");
        return 1;
    }
    //if key is too large, adjust it
    while (key > 26)
        {
            key = key - 26;
        }
    
    //get string input
    string message = get_string("plaintext: ");
    printf("ciphertext:");
    
    //create blank array for cryptic message
    int crypt[strlen(message)];
    
    //convert string input via key
    for (int i =0; i <strlen(message); i++)
    {   
        //preserve punctuation, spaces, etc.
        if (message[i] < 65 && message [i] > 31)
            {
                crypt[i] = message [i];
            }
        //preserve capitalizations
        else if (message[i] < 91 && message[i] > 64)
        {
            if ((message[i] + key) > 90)
            {
                crypt[i] = message[i] + key - 26;
            }
            else
            {
                crypt[i] = message[i] + key;
            }
            
        }
        else
        {
            if ((message[i] + key) > 122)
            {
                crypt[i] = (message[i] + key - 26);
            }
            else 
            {
                crypt[i] = (message[i] + key);
            }
        }
        
        //print result in letters
        printf("%c", (char)crypt[i]);
    }
    printf("\n");
    return 0;
}