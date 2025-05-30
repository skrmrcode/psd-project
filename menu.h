#ifndef MENU_H
#define MENU_H

#include "heap.h"

// Display the main menu options to the user
void showMenu();

// Handle the selected menu choice
void handleChoice(heap h, int choice);

// Start the main menu loop
void menuLoop(heap h);

#endif
