#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


//define some data types for ease of use
typedef uint8_t BYTE;
typedef uint32_t xBYTE;
const int HUGE = 5120000;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    //open memory card file
    FILE* old_file = fopen(argv[1], "r");

    //reject if file location invalid
    if (old_file == NULL)
    {
        printf("invalid file.\n");
        return 1;
    }
 
    //open new file
    FILE* new_file = fopen("newfile", "w");
    
    //read the old file into the buffer location until reach end of the file
    BYTE buffer[512];
    int counter = 0;
    while (fread(buffer, sizeof(BYTE), 512, old_file) != 0)
    {
        //if this is the beginning of a JPEG...
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (counter == 0)
            {
                //close old new_file
                fclose(new_file);
                
                //open new file to write to
                char name[8];
                sprintf(name, "%03i.jpg", counter);
                new_file = fopen(name, "w");
           
                //write the 512 byte chunk into the new file
                fwrite(buffer, sizeof(BYTE), 512, new_file);
                
                //add to the file counter
                counter++;
            }
            //if this is not the first beginning of JPEG
            else
            {
                //close the previous file
                fclose(new_file);
            
                //open new file to write to
                char name[8];
                sprintf(name, "%03i.jpg", counter);
                new_file = fopen(name, "w");
            
                //write the 512 byte chunk into the new file
                fwrite(buffer, sizeof(BYTE), 512, new_file);
                
                //add to the file counter
                counter++;
            }
            
        }
        //if not beginning of JPEG
        else 
        {
            //write information to current file
            fwrite(buffer, sizeof(BYTE), 512, new_file);
        }
    }

    //close old file
    fclose(old_file);
    
    //close most recent new file
    fclose(new_file);
}