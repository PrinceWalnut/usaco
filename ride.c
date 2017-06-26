/*
ID: rick.li1
LANG: C
TASK: ride
*/

/* Solution to 'Your Ride is Here' */

#include <stdio.h>
#include <stdlib.h>

// Will get numerical value of string
int multiply_letters_mod47(char* string)
{
    long product = 1;
    char *temp = string;
    
    while(*temp != '\0')
    {
        product *= *temp - 64;
        temp++;
    }

    int result = product % 47;
    return result;
}

int main()
{
    // Initialize strings for comet/group
    char comet_str[8];
    char group_str[8];

    // Initializing files for read/write
    FILE * input_file;
    input_file = fopen("ride.in", "r");
    FILE * output_file;
    output_file = fopen("ride.out", "w");
    
    // Go through ride.in and print commands to ride.out
    while(fscanf(input_file, "%s %s", comet_str, group_str) == 2)
    {
        if(multiply_letters_mod47(comet_str) == multiply_letters_mod47(group_str))
            fprintf(output_file, "GO\n");
        else
            fprintf(output_file, "STAY\n");
    }

    // Closing files
    fclose(input_file);
    fclose(output_file);

    return 0;
}
