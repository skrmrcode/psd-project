#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"


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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

// Save all activities from the heap into a formatted text file for persistence
void saveActivitiesToFile(heap h) {
    FILE *f = fopen("activities.txt", "w");
    if (!f) {
        printf("Unable to open file for writing.\n");
        return;
    }

    // Write header line
    fprintf(f, "%-20s | %-15s | %-10s | %4s | %5s | %6s | %-10s\n",
            "Description", "Course", "Deadline", "Time", "Prio", "Hours", "Created");

    // Write separator line
    fprintf(f, "------------------------------------------------------------------------------------------\n");

    // Write all activities in the heap
    int size = getNumElem(h);
    for (int i = 0; i < size; i++) {
        activity a = getActivity(h, i);

        // Save all necessary fields, including worked hours
        fprintf(f, "%-20s | %-15s | %-10s | %4d | %5d | %6d | %-10s\n",
                getDescr(a), getCourse(a), getDeadline(a),
                getTimeReq(a), getP(a), getWorkedHours(a), getCreatedDate(a));
    }

    fclose(f);
}

// Load activities from the file and add them to the heap
void loadActivitiesFromFile(heap h) {
    FILE *f = fopen("activities.txt", "r");
    if (!f) return;

    char line[512];
    char descr[256], course[100], deadline[11], created[11];
    int timereq, prio, worked_hours;

    // Skip header lines
    fgets(line, sizeof(line), f);
    fgets(line, sizeof(line), f);

    // Read each activity entry from file
    while (fgets(line, sizeof(line), f) != NULL) {
        // Parse activity fields from formatted line
        int parsed = sscanf(line, " %255[^|] | %99[^|] | %10[^|] | %d | %d | %d | %10s",
                            descr, course, deadline, &timereq, &prio, &worked_hours, created);
        if (parsed == 7) {
            // Remove trailing newline characters
            descr[strcspn(descr, "\r\n")] = 0;
            course[strcspn(course, "\r\n")] = 0;
            deadline[strcspn(deadline, "\r\n")] = 0;
            created[strcspn(created, "\r\n")] = 0;

            // Reconstruct the activity and add to heap
            activity a = newAct(descr, course, deadline, timereq, prio);
            setCreatedDate(a, created);
            updateProgress(a, worked_hours);
            addAct(h, a);
        }
    }

    fclose(f);
}

void clearInputBuffer() {
    while (getchar() != '\n');
}

int getIntInput(const char *prompt, int min, int max) {
    int value;
    char input[100];

    while (1) {
        printf("%s", prompt);
        if (!fgets(input, sizeof(input), stdin)) {
            printf("Input error. Try again.\n");
            continue;
        }

        // Rimuove newline
        input[strcspn(input, "\n")] = '\0';

        // Controlla che siano solo cifre (o segno negativo, se min < 0)
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
