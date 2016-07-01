#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover infile\n");
        return 1;
    }
    
    // remember filename
    char* infile = argv[1];
    
    // open input file 
    FILE* file = fopen(infile, "r");
    if (file == NULL)
    {
        printf("Could not open %s. \n", infile);
        return 1;
    }
    
    // variable to keep track for jpeg name
    int jpegName = 0;
    
    // pointer to output file
    FILE* img = NULL;
    
    // infinite loop to read from file
   while(0 < 1)
   {
        // temporary storage to keep a block of 512 bytes
        BYTE buffer[512];
    
        // reading 512 bytes
        if(fread(&buffer, 512 * sizeof(BYTE), 1, file) == 1)
        {
            // checking if a jpeg is found
            if((buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff) && (buffer[3] == 0xe0 || buffer[3] == 0xe1 || buffer[3] == 0xe2 || buffer[3] == 0xe3 || buffer[3] == 0xe4 || buffer[3] == 0xe5 || buffer[3] == 0xe6 || buffer[3] == 0xe7 || buffer[3] == 0xe8 || buffer[3] == 0xe9 || buffer[3] == 0xea || buffer[3] == 0xeb || buffer[3] == 0xec || buffer[3] == 0xed || buffer[3] == 0xee || buffer[3] == 0xef))
            {
                // checking && closing a jpg if one is already opened
                if(img != NULL)
                {
                 fclose(img);   
                }
                
                // creating a filename && opening a new file
                char title[sizeof "000.jpg"];
                
                sprintf(title, "%03d.jpg", jpegName);
                
                img = fopen(title, "a");
                if (img == NULL)
                {
                    fclose(file);
                    fprintf(stderr, "Could not create the image.\n");
                    return 2;
                }
                
                // writing block of 512 bytes to a jpg file
                fwrite(&buffer, 512 * sizeof(BYTE), 1, img);
                
                // update filename
                jpegName++;
            }
            
            // checking if a jpg is already created
            else if(img != NULL)
            {
                // writing block of 512 bytes to a jpg file
                fwrite(&buffer, 512 * sizeof(BYTE), 1, img);
            }
        }
        
        // breaking out of forever loop when EOF is reached
        else
        {
            break;
        }
    }
    
    // close input && output files
    fclose(file);
    fclose(img);
    return 0;
}
