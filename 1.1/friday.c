/*
ID: rick.li1
LANG: C
TASK: friday
*/

/* Solution to 'Friday the Thirteenth' */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Day
{
    unsigned int occurrences;
    struct Day * next;
};

int main()
{
    // Create days of the week
    struct Day saturday;
    struct Day sunday;
    struct Day monday;
    struct Day tuesday;
    struct Day wednesday;
    struct Day thursday;
    struct Day friday;

    saturday.next = &sunday;
    sunday.next = &monday;
    monday.next = &tuesday;
    tuesday.next = &wednesday;
    wednesday.next = &thursday;
    thursday.next = &friday;
    friday.next = &saturday;

    struct Day * temp = &saturday; // Jan 13, 1900 was a Saturday

    for(int i = 0; i < 7; i++)
    {
        temp->occurrences = 0;
        temp = temp->next;
    }
    saturday.occurrences = 1;

    // Some stuff to keep track of dates
    int year = 1900;
    int month = 1; // Jan = '1', Feb = '2', etc.

    // Open file streams
    FILE * input_file;
    input_file = fopen("friday.in", "r");
    FILE * output_file;
    output_file = fopen("friday.out", "w");

    // Retrieve number of years to test from friday.in; find ending year
    int num_years;
    fscanf(input_file, "%d", &num_years);
    int end_year = year + num_years; // 1900 + N years

/*
Solution will be to check what day the thirteenth of each month falls on by moving around the circularly linked list 'days' according to the number of days in the month (mod 7 of course). Leap years are taken into account when dealing with February.
*/
    int skip;

    // Year loop
    while(year < end_year)
    {
        //Month loop
        while(month <= 12)
        {
            // Will determine the number of days to skip ahead
            switch(month)
            {
                case 1:
                    skip = 31;
                    break;
                case 2: // Leap year cases
                    if(year % 4 != 0)
                        skip = 28;
                    else
                    {
                        if(year % 100 == 0 && year % 400 != 0)
                            skip = 28;
                        else
                            skip = 29;
                    }
                    break;
                case 3:
                    skip = 31;
                    break;
                case 4:
                    skip = 30;
                    break;
                case 5:
                    skip = 31;
                    break;
                case 6:
                    skip = 30;
                    break;
                case 7:
                    skip = 31;
                    break;
                case 8:
                    skip = 31;
                    break;
                case 9:
                    skip = 30;
                    break;
                case 10:
                    skip = 31;
                    break;
                case 11:
                    skip = 30;
                    break;
                case 12: 
                    skip = 31;
                    break;
            } // End of switch for skipped days
            if(year == end_year - 1 && month == 12)
                break;
            skip %= 7;
            // Skip to next 13th and increment
            for(int i = 0; i < skip; i++)
                temp = temp->next;
            temp->occurrences++;
            month++;
        } // End of month loopA
        month = 1;
        year++;
    } // End of year loop

    // Write results to file
    fprintf(output_file, "%u %u %u %u %u %u %u\n",
            saturday.occurrences,
            sunday.occurrences,
            monday.occurrences,
            tuesday.occurrences,
            wednesday.occurrences,
            thursday.occurrences,
            friday.occurrences);

    // Close files
    fclose(input_file);
    fclose(output_file);
}
