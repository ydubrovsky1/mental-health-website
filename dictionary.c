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
unsigned int counter;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    //hash word to obtain hash value
    unsigned int index = hash(word);
    //return false if nothing at that index value
    if (table[index] == NULL)
        return false;
    //create traversal pointer to head of list
    node *temp = table[index];
    //If current node val field what look for, report success
    while(temp != NULL)
    {
        if(strcasecmp(word, temp -> word) == 0)
            return true;
        temp = temp -> next;
    }
    return false;
    //traverse linked list, looking for the word
}

// Hashes word to a number
// djb2 hash function from http://www.cse.yorku.ca/~oz/hash.html
unsigned int hash(const char *word)
{
    // TODO (input word/(alpha ''), output index 0 to N-1
    //set has per function specs of djb2
    unsigned int hash = 5381;
    int c;
    
    //iterate through each char 
    while ((c = *word++))
    {
        //actual hash function(shift hash value left 5 bits, add this to value of lowercase c)
        hash = ((hash <<5) + hash) + tolower(c); 
    }
    //return int hash, modulated by size of hashtable
    return hash % N;
    return 0;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    //open dictionary file
    FILE *D_open = fopen(dictionary, "r");
    if (D_open == NULL)
    {
        printf("invalid dictionary.\n");
        return false;
    }
    //allocate memory for buffer
    char *buffer = malloc(sizeof(char) * LENGTH);
    
    //initialize counter
    counter = 0;
    
    //allocate space for a node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("insufficient memory for nodes.\n");
            return false;
        }
    //read words from file into buffer, one string at a time
    while (fscanf(D_open, "%s", buffer) != EOF)
    {
        //copy word into node
        strcpy(n -> word, buffer);
        
        //increase word counter
        counter = counter + 1;
        
        //hash the node
        int index = hash(n -> word);
        
        //insert node into linked list
        n -> next = table[index];
        table[index] = n;
        
        //allocate space for a node
        n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("insufficient memory for nodes.\n");
            return false;
        }
    }
    free(n);
    free(buffer);
    return true;

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
   return counter; 
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    //cycle through the table of pointers
    for(int i = 0; i < N; i++)
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
    return true;
}
