#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include "heap.h"

// Check if a string is a valid date in YYYY-MM-DD format
int isValidDate(const char *date);

// Load activities from the file and add them to the heap
void loadActivitiesFromFile(heap h);

// Save all current activities from the heap to the file
void saveActivitiesToFile(heap h);

// Clear remaining characters from the input buffer
void clearInputBuffer();

// Prompt the user for an integer input within the specified range
int getIntInput(const char *prompt, int min, int max);

#endif
