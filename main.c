#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "heap.h"

//display menu
void showmenu(){
    printf("\n---  Planning and Monitoring System\n");
    printf("1. Add study activity\n");
    printf("2. Upgrade progress\n");
    printf("3. View activities\n");
    printf("4. Generate weekly report\n");
    printf("0. Close\n");
    printf("Scelta: ");
}

int main(){
    heap h = newHeap(100);
    int choice;

    while(1){
        scanf("%d", &choice);
        getchar(); //"delete" the new line

        switch (choice)
        {
        case 0:
            break;

        case 1:
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

            activity a = newact(descr, course, deadline, time, p);
            addAct(h, a);

        case 2:
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

        case 3:
            printHeap(h);
        
        case 4:
        printf("\n--- Weekly Report ---\n");
            int num = getNumElem(h);
            for (int i = 0; i < num; i++) {
                activity a = getActivity(h, i);
                if (getState(a) == COMPLETED) {
                    printf("[COMPLETED] ");
                } else if (isLate(a)) {
                    printf("[OVERDUE] ");
                } else {
                    printf("[ONGOING] ");
                }
                printAct(a);
                
        default:
            break;
        }
    }
}