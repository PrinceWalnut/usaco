/*
ID: rick.li1
LANG: C
TASK: beads
*/

/* Solution to 'Broken Necklace' */

#include <stdlib.h>
#include <stdio.h>

struct Bead
{
    char color;
    struct Bead * prev;
    struct Bead * next;
};

int main()
{
    // Open files
    FILE * input_file;
    input_file = fopen("beads.in", "r");
    FILE * output_file;
    output_file = fopen("beads.out", "w");

    // Read length of necklace
    int necklace_length;
    fscanf(input_file, "%d\n", &necklace_length);

    struct Bead temp_beads[necklace_length];
    // Read colors from file and generate circular linked list for necklace
    for(int i = 0; i < necklace_length; i++)
    {
        temp_beads[i].color = fgetc(input_file); 
        if(i == 0)
            temp_beads[i].prev = &temp_beads[necklace_length-1];
        else
            temp_beads[i].prev = &temp_beads[i-1];
        if(i + 1 == necklace_length)
        {
            temp_beads[i].next = &temp_beads[0];
            break;
        }
        temp_beads[i].next = &temp_beads[i+1];
    }

    // Traverse points in necklace checking total sum of same color beads in each direction; store best solution in 'profit' 
    struct Bead *temp = &temp_beads[0];
    int profit = 0;
    int maybe_profit = 0;
    char color;
    struct Bead *temp2 = temp;
    int num_iterations;

    for(int i = 0; i <= necklace_length; i++)
    {
        num_iterations = 0;
        temp2 = temp;
        color = temp2->color;
        // Iterate forward from cut point (cut point is right before temp)
        while((temp2->color == color || temp2->color == 'w') && num_iterations < necklace_length)
        {
            num_iterations++;
            maybe_profit++;
            temp2 = temp2->next;
            if(color == 'w')
                color = temp2->color;
        }

        // Iterate backward from cut point
        temp2 = temp->prev;
        color = temp2->color;
        while((temp2->color == color || temp2->color == 'w') && num_iterations < necklace_length)
        {
            num_iterations++;
            maybe_profit++;
            temp2 = temp2->prev;
            if(color == 'w')
                color = temp2->color;
        }
        if(num_iterations == necklace_length)
        {
            profit = necklace_length;
            break;
        }
        
        if(maybe_profit > profit)
            profit = maybe_profit;
        maybe_profit = 0;
        temp = temp->next;
    }

    // Write result to output file
    fprintf(output_file, "%d\n", profit);

    // Close files
    fclose(input_file);
    fclose(output_file);   
}
