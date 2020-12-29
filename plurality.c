#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // if name match candidate update vote total, return true
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes = candidates[i].votes + 1;
            return true;
        }
    }
    //if not match candidate name don't change total, return false
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // set bubble sort counter to non-zero number
    int a = 1; 
    while (a != 0)
    {
        //keep swapping consecutive numbers until all in order
        for (int i = 0; i < candidate_count; i++)
        {   
            a = 0; 
            if (candidates[i].votes > candidates[i+1].votes)
            {
                candidate swap1 = candidates[i];
                candidate swap2 = candidates[i+1];
                candidates[i] = swap2;
                candidates[i+1] = swap1;
                a = a + 1; 
            }
        }
            
    }
    //print the winner (person in final array position got most votes)
    printf("\n%s", candidates[candidate_count].name);
    for (int i = 1; i < candidate_count; i++)
        {
            if (candidates[candidate_count - i].votes == candidates[candidate_count].votes)
                printf("\n%s", candidates[candidate_count - i].name);
    
    return;
}
}

