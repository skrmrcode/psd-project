#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "menu.h"
#include "utils.h"

// Display the available menu options
void showMenu() {
    printf("\n---  Planning and Monitoring System\n");
    printf("1. Add study activity\n");
    printf("2. Upgrade progress\n");
    printf("3. View activities\n");
    printf("4. Generate weekly report\n");
    printf("0. Close\n");
}

// Handle user choice from the menu
void handleChoice(heap h, int choice) {
    switch (choice) {
        case 0:
            exit(0);  // Exit the program

        case 1: {
            // Add a new study activity
            char descr[256], course[100], deadline[11], created[11];
            int timereq, p;

            printf("Description: ");
            fgets(descr, sizeof(descr), stdin);
            descr[strcspn(descr, "\n")] = 0;

            printf("Course: ");
            fgets(course, sizeof(course), stdin);
            course[strcspn(course, "\n")] = 0;

            // Validate deadline format
            do {
                printf("Deadline (YYYY-MM-DD): ");
                fgets(deadline, sizeof(deadline), stdin);
                deadline[strcspn(deadline, "\n")] = 0;

                if (!isValidDate(deadline)) {
                    printf("Invalid date format. Please try again.\n");
                }
            } while (!isValidDate(deadline));

            timereq = getIntInput("Estimated time (numeric only): ", 1, 1000);
            p = getIntInput("Priority (1 = Low, 2 = Medium, 3 = High): ", 1, 3);

            time_t now = time(NULL);
            strftime(created, sizeof(created), "%Y-%m-%d", localtime(&now));

            activity a = newAct(descr, course, deadline, timereq, p);
            setCreatedDate(a, created);
            addAct(h, a);
            saveActivitiesToFile(h);
            break;
        }

        case 2: {
            // Update progress on a selected activity
            int num = getNumElem(h);
            if (num == 0) {
                printf("No activities available.\n");
                break;
            }

            int idx = getIntInput("Choose the activity index: ", 0, num - 1);
            int hour = getIntInput("Hours to add: ", 1, 1000);

            activity a = getActivity(h, idx);
            if (a != NULL) {
                updateProgress(a, hour);
                saveActivitiesToFile(h);
            } else {
                printf("Invalid index!\n");
            }
            break;
        }

        case 3: {
            // Display all activities
            printf("\n%-4s %-20s %-15s %-12s %-8s %-6s\n", "ID", "Description", "Course", "Deadline", "Hours", "Prio");
            printf("-------------------------------------------------------------------------------\n");
            int num = getNumElem(h);
            for (int i = 0; i < num; i++) {
                activity a = getActivity(h, i);
                printf("%-4d %-20s %-15s %-12s %-8d %-6d\n", i, getDescr(a), getCourse(a), getDeadline(a), getWorkedHours(a), getP(a));
            }
            break;
        }

        case 4: {
            // Generate and save weekly report to file
            printf("\n--- Weekly Report ---\n");
            FILE *f = fopen("report.txt", "w");
            if (f == NULL) {
                printf("Error creating report file!\n");
                return;
            }

            fprintf(f, "%-12s %-20s %-15s %-12s %-8s %-6s\n", "Status", "Description", "Course", "Deadline", "Hours", "Prio");
            fprintf(f, "------------------------------------------------------------------------------------------\n");

            printf("%-12s %-20s %-15s %-12s %-8s %-6s\n", "Status", "Description", "Course", "Deadline", "Hours", "Prio");
            printf("------------------------------------------------------------------------------------------\n");

            int num = getNumElem(h);
            for (int i = 0; i < num; i++) {
                activity a = getActivity(h, i);
                const char *status;
                if (getState(a) == COMPLETED) {
                    status = "COMPLETED";
                } else if (isLate(a)) {
                    status = "OVERDUE";
                } else {
                    status = "ONGOING";
                }

                fprintf(f, "%-12s %-20s %-15s %-12s %-8d %-6s\n",
                        status, getDescr(a), getCourse(a), getDeadline(a), getWorkedHours(a), priorityToStr(getP(a)));
                printf("%-12s %-20s %-15s %-12s %-8d %-6s\n",
                       status, getDescr(a), getCourse(a), getDeadline(a), getWorkedHours(a), priorityToStr(getP(a)));
            }

            fclose(f);
            printf("Report saved to 'report.txt'\n");
            break;
        }

        default:
            printf("Invalid choice!\n");
            break;
    }
}

// Loop to repeatedly show menu until the user exits
void menuLoop(heap h) {
    while (1) {
        showMenu();
        int choice = getIntInput("Choice: ", 0, 4);
        if (choice == -1) {
            printf("Error reading input. Exiting.\n");
            exit(1);
        }
        handleChoice(h, choice);
    }
}
