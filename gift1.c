/*
ID: rick.li1
LANG: C
TASK: gift1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person
{
    char name[16];
    int given;
    int received;
};

// Updates information for each Person; input of -1 indicates no change
void update_info(struct Person* list, char* name, int given, int received)
{
    struct Person *temp = list;
    while(strcmp(temp->name, name) != 0)
        temp++;
    if(given != -1)
        temp->given += given;
    if(received != -1)
        temp->received += received; 
}

int main()
{
    // Open files for read/write
    FILE * input_file;
    input_file = fopen("gift1.in", "r");
    FILE * output_file;
    output_file = fopen("gift1.out", "w");

    // Get number of friends and read them in
    int num_friends;
    fscanf(input_file, "%d", &num_friends);

    struct Person friends[num_friends];
    
    for (int i = 0; i < num_friends; i++)
    {
        fscanf(input_file, "%s", friends[i].name);
        friends[i].given = 0;
        friends[i].received = 0;
    }

    // Read in gifts and recipients for each person
    for(int i = 0; i < num_friends; i++)
    {
        char giver_name[16];
        int amount_given;
        int num_given_to;
        int amount_received;
        fscanf(input_file, "%s %d %d", giver_name, &amount_given, &num_given_to);

        // In case of a greedy bastard
        if(num_given_to == 0)
            continue;

        // Update amount given to account for no fractional money
        amount_given -= amount_given % num_given_to;
        amount_received = amount_given / num_given_to;       
        update_info(friends, giver_name, amount_given, -1);        

        // Update received amount for each recipient
        for(int j = 0; j < num_given_to; j++)
        {
            char recipient_name[16];
            fscanf(input_file, "%s", recipient_name);
            update_info(friends, recipient_name, -1, amount_received);
        }
    }

    for(int i = 0; i < num_friends; i++)
    {
        int net_gain = friends[i].received - friends[i].given;
        fprintf(output_file, "%s %d\n", friends[i].name, net_gain);
    }

    // Closing files
    fclose(input_file);
    fclose(output_file);

    return 0;
}
