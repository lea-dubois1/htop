#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "../headers/dataManager.h"
#include "../headers/displayHandler.h"

int main()
{
    char *input = (char*)malloc(sizeof(char) * 2);
    do {
        free(input);
        input = (char*)malloc(sizeof(char) * 2);
        getData();
        printf("\nCliquez sur R pour raffraichir et sur Q pour sortir.\n");
        scanf("%s", input);
        if(strcmp(input, "q") == 0 || strcmp(input, "Q") == 0){
            break;
        }
    } while (strcmp(input, "r") == 0 || strcmp(input, "R") == 0);
}
