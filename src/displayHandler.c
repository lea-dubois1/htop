#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curses.h>

#include "../headers/displayHandler.h"
#include "../headers/dataManager.h"

void display(Process *processes)
{
    initscr();




    for (int i = 0; processes[i].id != '\0' && strcmp(processes[i].name, "\0") != 0; i++) {
        printf("Process number %i : %s\n", processes[i].id, processes[i].name);
    }
}