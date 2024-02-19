#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curses.h>
#include <ctype.h>

#include "../headers/displayHandler.h"
#include "../headers/dataManager.h"

#define NUM_STRING 100

//void display(Process *processes)
void display() {
//    int startRow = 1;
    int ch;

    initscr(); // Initialiser ncurses

    WINDOW *cpu_win = subwin(stdscr, LINES / 5, COLS, 0, 0); // Créer une fenêtre
    WINDOW *boite = subwin(stdscr, LINES / 5 * 4, COLS, LINES / 5, 0);

    cbreak(); // Désactiver la mise en mémoire tampon de ligne
    noecho(); // Désactiver l'affichage de l'entrée utilisateur

    wrefresh(cpu_win); // Rafraîchir la fenêtre
    wrefresh(boite);

    scrollok(cpu_win, true);
    scrollok(boite, true);
    keypad(stdscr, TRUE); // Activer les touches spéciales


    do
    {
        wclear(cpu_win);
        wclear(boite);

        box(cpu_win, 0, 0);
        box(boite, 0, 0);

        mvwprintw(cpu_win, 1, 1, "HELLO");

        wrefresh(cpu_win);
        wrefresh(boite);
        refresh();
    }
    while ((ch = toupper(getch())) != 'Q');

    endwin(); // Terminer ncurses


//    for (int i = 0; processes[i].id != '\0' && strcmp(processes[i].name, "\0") != 0; i++) {
//        printf("Process number %i : %s\n", processes[i].id, processes[i].name);
//    }
}