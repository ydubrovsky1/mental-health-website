#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
 
 
//define some data types for ease of use
typedef uint8_t BYTE;
typedef uint32_t xBYTE;
int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    
    //open memory card file
    FILE *old_file = fopen(argv[1], "r");
 
    //reject if file location invalid
    if (old_file == NULL)
    {
        printf("invalid file.");
        return 1; 
    }
    
    //read the old file into a buffer array until reach end of the file
    BYTE buffer[512 * 60];
    while (fread(buffer, sizeof(BYTE), 512 * 60, old_file) != 0)
    {
        fread(buffer, sizeof(BYTE), 512 * 60, old_file);
    }
    //read through the array looking for JPEGs
    for (int i = 0; i <(512 * 60); i = (i + 512))
    {
        //if this is the beginning of a JPEG...
        if (buffer[i] == 0xe0 && buffer [i + 1] == 0xd8 && buffer [i + 2] == 0xff && buffer [i + 3] == (0xe0 | 0xe1 | 0xe2 | 0xe3 | 0xe4 | 0xe5 | 0xe6 | 0xe7 | 0xe8 | 0xe9 | 0xea | 0xeb | 0xec | 0xed | 0xee | 0xef))
        {
            //open new file to write to 
            char name[8];
            sprintf(name, "%i.jpg", i);
            FILE *new_file = fopen(name , "w");
            //write the 512 byte chunk into the new file
            fwrite(buffer, sizeof(BYTE), 512, new_file);
            //loop through subsequent chunks, continuing to write. if get to new JPEG, exit this loop
            for (int j = (i + 512); j <(512*60); j = j + 152)
            {
                if (buffer[j] == 0xe0 && buffer [j + 1] == 0xd8 && buffer [j + 2] == 0xff && buffer [j + 3] == (0xe0 | 0xe1 | 0xe2 | 0xe3 | 0xe4 | 0xe5 | 0xe6 | 0xe7 | 0xe8 | 0xe9 | 0xea | 0xeb | 0xec | 0xed | 0xee | 0xef))
                {
                    j = (512 * 60);
                }
                else
                {
                    fwrite(buffer, sizeof(BYTE), 512, new_file);
                }
                
            }
        }
    }
    
    //close old file
    fclose(old_file);
}