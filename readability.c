
#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(void)
{
    int letters = 0;
    int words = 1;
    int sentences = 0;
    float index = 0;
    string text = get_string("Text:\n");
    
    
    for (int i = 0; i < strlen(text); i++)
    {   
       if isalpha (text[i]) 
       { 
           letters = letters +1;
       }
       if isspace (text[i])
       {
           words = words +1;
       }
       if (text[i] =='!' || text[i] =='.' || text[i] =='?')
       {
           sentences = sentences +1;
       }
    }
    
index = .0588*((float)letters/((float)words/(float)100))- .296*((float)sentences/((float)words/(float)100)) - 15.8;
int grade = round(index);

if (grade < 1)
{
printf("Before Grade 1\n");
}
else if (grade >= 16)
{
    printf("Grade 16+\n");
}
else
{
    printf("Grade %i\n", grade);
}
}



