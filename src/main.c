#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../headers/dataManager.h"
#include "../headers/displayHandler.h"

int main()
{
    char input = 'R';
    Process *processes = malloc(sizeof(Process));
    do {
        switch (input) {
            case 'R':
                processes = getData(processes);
                display(processes);
                break;

            default:
                break;
        }
        printf("\nCliquez sur R pour raffraichir et sur Q pour sortir.\n");
        input = toupper(getchar());

        if(input == '\n'){
            input = toupper(getchar());
        }
    } while (input != 'Q');
    return 0;
}
