#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void significantFig(char *input)
{
    // the number of sig. figures, '.' chars and '0' chars... also the length
    int sigCount, pdCount, zeroCount, len; 
    len = pdCount = zeroCount = sigCount = 0; 

    len = strlen(input) + 1; 

    unsigned int j; 
    for (j = 0; j < strlen(input); j++)
    {
        // check for '0' and '.' chars
        if (input[j] == '0')
        {
            zeroCount++; 
        }

        if (input[j] == '.')
        {
            pdCount++;

            // cannot be more than one period in a floating point number 
            if(pdCount > 1)
            {
                printf("Error: too many periods in float argument.\n"); 
                return; 
            }
        }
    }


    unsigned int i; 
    for (i = 0; i < strlen(input); i++)
    {
        // check if i passed a 'number'  or a period
        if( (isdigit(input[i]) == 0) && input[i] != '.')
        {
            printf("Error: expected numeric, received non-numeric.\n");
            return; 
        }

        // if the input is a numeric char, then verify the conditions to count the number of significant digits 
        else 
        {
            // all non-zeroes are significant 
            if (input[i] != '0' && input[i] != '.')
            {
                sigCount++; 
            }
            
            if (len > 3)
            {
                // trailing zeros don't count 
                if (input[i] == '0' && input[i + 1] == '\0' && pdCount == 0)
                {
                    sigCount += 0; 

                }

                // if a period has been passed then the 0's after are significant 
                else if (input[i] == '0' && input[i + 1] != '\0'  && pdCount == 1)
                {
                    sigCount++; 
                }

                // leading zeros aren't significant 
                if (input[i] == '0' && i == 0)
                {
                    sigCount += 0; 
                }
                
                // if the char b/f and after the 0 isn't 0 or a . then increment the count
                else if (input[i] == '0' && i != 0 && input[i + 1] != '0' && input[i - 1] != '0' && input[i + 1] != '.' && 
                         input[i - 1] != '.' && input[i + 1] != '\0')
                {
                    sigCount++;
                 
                }
            }

            // zeroes after the decimal are significant 
            if (len > 3)
            {
                if (i != 0 )
                {
                    if (input[i - 1] == '.' &&  pdCount == 1 && input[i] == '0')
                    {
                        sigCount++; 
                    }
                }
                
                if (input[0] == '0' && input[i + 1] != '0' && pdCount == 1 && input[i + 2] != '0'  && input[i + 2] != '.')
                {
                    sigCount += 0; 
                }

                if (input[0] == '0' && zeroCount == 1 && input[i + 1] == '.')
                {
                    sigCount--; 
                }
            }
        }
    }

    printf("The number of significant figures is: %d\n", sigCount);

    return; 
}







int main (int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Error: amount of command line arguments is invalid.\n"); 
        printf("Usage: ./sigfig [int or floating point number]\n");
        return -1; 
    }

    // copy the string into a buffer, then pass it to the function
    char *number = malloc(sizeof(char) * (strlen(argv[1]) + 1)); 

    strcpy(number, argv[1]); 
    significantFig(number);

    free(number);  // ALWAYS FREE THE MEMORY!
    return 0; 
}