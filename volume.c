// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;
typedef uint8_t BYTE;
typedef int16_t sBYTE;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    //read header from input file
    BYTE header[44];
    fread(header, sizeof(BYTE), HEADER_SIZE, input);
    //write header to output file
    fwrite(header, sizeof(BYTE), HEADER_SIZE, output);
    

    // TODO: Read samples from input file and write updated data to output file
    
    //for each 2-byte sample:
    sBYTE buffer;
        //read sample from input file
        while (fread(&buffer, sizeof(BYTE), 2, input) != 0)
        {
            //multiply by volume factor
            buffer = buffer * factor;
            //write to output file
            fwrite(&buffer, sizeof(BYTE), 2, output);
        }
    //free up allocated memory
    
    // Close files
    fclose(input);
    fclose(output);
    return 0;
}
