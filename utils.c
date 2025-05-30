#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

// Check if a string is a valid date in YYYY-MM-DD format
int isValidDate(const char *date) {
    if (strlen(date) != 10) return 0;
    if (date[4] != '-' || date[7] != '-') return 0;

    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(date[i])) return 0;
    }

    int year = atoi(date);
    int month = atoi(date + 5);
    int day = atoi(date + 8);

    if (month < 1 || month > 12) return 0;
    if (day < 1 || day > 31) return 0;

    if (month == 2 && day > 29) return 0;
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return 0;

    return 1;
}

// Load activities from the "activities.txt" file and add them to the heap
void loadActivitiesFromFile(heap h) {
    FILE *f = fopen("activities.txt", "r");
    if (f == NULL) {
        printf("No saved activities found.\n");
        return;
    }

    char line[512];
    int lineNum = 0;

    while (fgets(line, sizeof(line), f)) {
        lineNum++;
        if (lineNum <= 2) continue;  // Skip header lines

        char descr[256], course[100], deadline[11], created[11];
        int timereq, prio;

        int scanned = sscanf(line, " %255[^|] | %99[^|] | %10[^|] | %d | %d | %10s",
                             descr, course, deadline, &timereq, &prio, created);
        if (scanned == 6) {
            descr[strcspn(descr, "\r\n")] = 0;
            course[strcspn(course, "\r\n")] = 0;
            deadline[strcspn(deadline, "\r\n")] = 0;
            created[strcspn(created, "\r\n")] = 0;

            activity a = newAct(descr, course, deadline, timereq, prio);
            setCreatedDate(a, created);
            addAct(h, a);
        }
    }
    fclose(f);
}

// Save all current activities in the heap to "activities.txt"
void saveActivitiesToFile(heap h) {
    FILE *f = fopen("activities.txt", "w");
    if (f == NULL) {
        printf("Error opening activities.txt for writing!\n");
        return;
    }

    fprintf(f, "%-20s | %-15s | %-10s | %4s | %4s | %-10s\n",
            "Description", "Course", "Deadline", "Time", "Prio", "Created");
    fprintf(f, "--------------------------------------------------------------------------------\n");

    int num = getNumElem(h);
    for (int i = 0; i < num; i++) {
        activity a = getActivity(h, i);
        fprintf(f, "%-20s | %-15s | %-10s | %4d | %4d | %-10s\n",
                getDescr(a), getCourse(a), getDeadline(a), getTimeReq(a), getP(a), getCreatedDate(a));
    }

    fclose(f);
}

// Clear remaining characters from the input buffer
void clearInputBuffer() {
    while (getchar() != '\n');
}

// Prompt the user for a valid integer within a given range
int getIntInput(const char *prompt, int min, int max) {
    int value;
    char input[100];

    while (1) {
        printf("%s", prompt);
        if (!fgets(input, sizeof(input), stdin)) {
            printf("Input error. Try again.\n");
            continue;
        }

        input[strcspn(input, "\n")] = '\0';

        char *endptr;
        value = (int)strtol(input, &endptr, 10);

        if (*endptr != '\0') {
            printf("Please enter a valid integer.\n");
            continue;
        }

        if (value < min || value > max) {
            printf("Please enter a value between %d and %d.\n", min, max);
            continue;
        }

        return value;
    }
}
