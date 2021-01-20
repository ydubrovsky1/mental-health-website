// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 100;

// Hash table 
node *table[N];

//create global variable counter
unsigned int counter = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //hash word to obtain hash value
    unsigned int index = hash(word);
    //return false if nothing at that index value
    if (table[index] == NULL)
    {
        return false;
    }
    //create traversal pointer to head of list
    node *temp = table[index];
    //If current node val field what look for, report success
    while(temp != NULL)
    {
        if(strcasecmp(word, temp -> word) == 0)
        {
            return true;
        }
        temp = temp -> next;
    }
    return false;
}

// Hashes word to a number
// https://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)HashTables.html?highlight=%28CategoryAlgorithmNotes%29 Hash functions
//also referenced in https://cs50.stackexchange.com/questions/37209/pset5-speller-hash-function
unsigned int hash(const char *word)
{
    // (input word, output index 0 to N-1
    unsigned int hash = 0;
    int c;
    for (int i = 0, n = strlen(word); i < n; i++)
        {
             hash = (hash << 2) ^ tolower(word[i]);
        }
        return hash % N; 
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //open dictionary file
    FILE *D_open = fopen(dictionary, "r");
    if (D_open == NULL)
    {
        printf("invalid dictionary.\n");
        return false;
    }
    //allocate memory for buffer
    char *buffer = malloc(sizeof(char) * LENGTH);
    if (buffer == NULL)
    {
        printf("insufficent memory for buffer.\n");
        fclose(D_open);
        return false;
    }
    
    //initialize counter
    counter = 0;
    
    //read words from file into buffer, one string at a time
    while (fscanf(D_open, "%s", buffer) != EOF)
    {
        //allocate space for a node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("insufficient memory for nodes.\n");
            free(buffer);
            fclose(D_open);
            return false;
        }
        //copy word into node
        strcpy(n -> word, buffer);
        //initialize next of node n
        n -> next = NULL;
        
        //increase word counter
        counter = counter + 1;
    
        //hash the node
        int index = hash(n -> word);
        
        //add the node if it's first to link to this index location
        if(table[index] == NULL)
        {
            table[index] = n;
            n -> next = NULL;
        }
        //add the node if there's already a linked node at index location
        else 
        {
           n -> next = table[index];
           table[index] = n;
        }
      
    }
    //close file
    fclose(D_open);
     //free buffer
    free(buffer);
    return true;

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
   if(counter > 0)
        return counter; 
    else
        return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    //cycle through the table of pointers
    for(int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            node *cursor = table[i];
            node *temp = table[i];
            while (cursor -> next != NULL)
            {
                cursor = cursor -> next;
                free(temp);
                temp = cursor;
            }
            free(temp);
        }
    }
    return true;
}
