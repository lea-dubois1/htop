#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curses.h>
#include <ctype.h>

#include "../headers/displayHandler.h"
#include "../headers/dataManager.h"

#define NUM_STRING 100
#define NB_DISPLAYED_LINES 34

//void display(Process *processes)
void display() {
    int startRow = 0;
    int ch;
    int processesLength = 0;
    Process *processes;

    initscr(); // Initialiser ncurses

    WINDOW *cpu_win = subwin(stdscr, LINES / 5, COLS, 0, 0); // Créer une fenêtre
    WINDOW *boite = subwin(stdscr, LINES / 5 * 4, COLS, LINES / 5, 0);

    cbreak(); // Désactiver la mise en mémoire tampon de ligne
    noecho(); // Désactiver l'affichage de l'entrée utilisateur

    wrefresh(cpu_win); // Rafraîchir la fenêtre
    wrefresh(boite);

    scrollok(cpu_win, true);
    scrollok(boite, true);
    keypad(stdscr, true); // Activer les touches spéciales

    while (true)
    {
        wclear(cpu_win);
        wclear(boite);

        box(cpu_win, 0, 0);
        box(boite, 0, 0);

        processesLength = getNumberProcesses(BASE_DIR_NAME);

        processes = getData();

        for (int arrayRow = startRow; arrayRow < startRow + LINES && arrayRow < processesLength; ++arrayRow) {
            mvwprintw(boite, arrayRow - startRow + 1, 2, "ID : %d, Name : %s", processes[arrayRow].id, processes[arrayRow].name);
        }

        switch((ch = getch())){
            case KEY_UP:
                if (startRow > 0) {
                    startRow--;
                }
                break;

            case KEY_DOWN:
                if (processesLength - startRow > NB_DISPLAYED_LINES - 1) {
                    startRow++;
                }
                break;

            case 'q':
            case 'Q':
                wclear(cpu_win);
                wclear(boite);
                endwin();
                return;

            default:
                break;
        }

        wrefresh(cpu_win);
        wrefresh(boite);
        refresh();
        free(processes);
    }

}