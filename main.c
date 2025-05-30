#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "heap.h"
#include "menu.h"
#include "utils.h"

// Entry point of the program
int main() {
    heap h = newHeap(100);         // Create a new heap with capacity 100
    loadActivitiesFromFile(h);     // Load previously saved activities from file
    int choice;

    while (1) {
        menuLoop(h);               // Display the menu and handle user interactions
        scanf("%d", &choice);
        getchar();                 // Clear the newline from input buffer
        handleChoice(h, choice);   // Process user's menu selection
    }
}
