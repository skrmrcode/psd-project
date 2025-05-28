// menu.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "menu.h"
#include "activity.h"

void showMenu() {
    printf("\n---  Planning and Monitoring System\n");
    printf("1. Add study activity\n");
    printf("2. Upgrade progress\n");
    printf("3. View activities\n");
    printf("4. Generate weekly report\n");
    printf("0. Close\n");
    printf("Choice: ");
}

void handleChoice(heap h, int choice) {
    switch (choice) {
        case 0:
            exit(0);

        case 1: {
            char descr[256], course[100], deadline[11];
            int time, p;
            printf("Description: ");
            fgets(descr, sizeof(descr), stdin);
            descr[strcspn(descr, "\n")] = 0;

            printf("Course: ");
            fgets(course, sizeof(course), stdin);
            course[strcspn(course, "\n")] = 0;

            printf("Deadline (YYYY-MM-DD): ");
            fgets(deadline, sizeof(deadline), stdin);
            deadline[strcspn(deadline, "\n")] = 0;

            printf("Estimated time: ");
            scanf("%d", &time);
            printf("Priority (1 = Low, 2 = Medium, 3 = High): ");
            scanf("%d", &p); getchar();

            activity a = newAct(descr, course, deadline, time, p);
            addAct(h, a);

            FILE *f = fopen("activities.txt", "a");
            if (f != NULL) {
                fprintf(f, "%s|%s|%s|%d|%d\n", descr, course, deadline, time, p);
                fclose(f);
            } else {
                printf("Error opening activities.txt!\n");
            }
            break;
        }

        case 2: {
            int num = getNumElem(h);
            printf("Choose the activity to update (from 0 to %d): ", num - 1);
            int idx, hour;
            scanf("%d", &idx);
            printf("Hours to add: ");
            scanf("%d", &hour); getchar();

            activity a = getActivity(h, idx);
            if (a != NULL) {
                updateProgress(a, hour);
            } else {
                printf("Invalid idx!\n");
            }
            break;
        }

        case 3:
            printHeap(h);
            break;

        case 4: {
            printf("\n--- Weekly Report ---\n");
            FILE *f = fopen("report.txt", "w");
            if (f == NULL) {
                printf("Error occurred creating report!\n");
                return;
            }

            int num = getNumElem(h);
            for (int i = 0; i < num; i++) {
                activity a = getActivity(h, i);
                if (getState(a) == COMPLETED) {
                    printf("[COMPLETED] ");
                    fprintf(f, "[COMPLETED] ");
                } else if (isLate(a)) {
                    printf("[OVERDUE] ");
                    fprintf(f, "[OVERDUE] ");
                } else {
                    printf("[ONGOING] ");
                    fprintf(f, "[ONGOING] ");
                }
                printAct(a);
                fprintf(f, "%s|%s|%s|%d hours\n", getDescr(a), getCourse(a), getDeadline(a), getWorkedHours(a));
            }

            fclose(f);
            printf("Report saved in 'report.txt'\n");
            break;
        }

        default:
            printf("Invalid choice!\n");
            break;
    }
}

void loadActivities(heap h) {
    FILE *f = fopen("activities.txt", "r");
    if (!f) return;

    char descr[256], course[100], deadline[11];
    int time, p;

    while (fscanf(f, " %255[^|]|%99[^|]|%10[^|]|%d|%d\n", descr, course, deadline, &time, &p) == 5) {
        activity a = newAct(descr, course, deadline, time, p);
        addAct(h, a);
    }

    fclose(f);
}

