#include <stdio.h>
#include <cs50.h>

int main(void)
{ int n;

    do
    {
       n = get_int("Height?:\n");
    }
    while (n < 1 || n > 8); 
    
    
    for (int x = 0; x < n; x++)
    { 
        for (int z = 1; z < (n-x); z++)
        {printf(" ");
        }
        for (int y = 0; y <= x; y++)
        {printf("#");
        }
    
        printf("\n");
    }
        
    }