#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "activity.h"

// Structure representing a study activity
struct c_act {
    char description[256];      // Activity description
    char course[100];           // Related course name
    char deadline[11];          // Deadline in YYYY-MM-DD format
    char created[11];           // Creation date in YYYY-MM-DD format
    int estimatedActTime;       // Estimated time to complete the activity (in hours)
    int timeSpentAct;           // Time already spent on the activity (in hours)
    priority p;                 // Activity priority (Low, Medium, High)
    c_state state;              // Current state of the activity
};

// Create and initialize a new activity
activity newAct(char *descr, char *course, char *deadline, int time, priority p) {
    activity a = malloc(sizeof(struct c_act));
    strncpy(a->description, descr, sizeof(a->description));
    strncpy(a->course, course, sizeof(a->course));
    strncpy(a->deadline, deadline, sizeof(a->deadline));
    a->estimatedActTime = time;
    a->timeSpentAct = 0;
    a->p = p;
    a->state = UNCOMPLETED;
    a->created[0] = '\0';  // Initialize as empty string
    return a;
}

// Update the amount of hours spent on the activity and its state
void updateProgress(activity a, int hours) {
    a->timeSpentAct += hours;
    if (a->timeSpentAct >= a->estimatedActTime) {
        a->state = COMPLETED;
    } else {
        a->state = ONGOING;
    }
}

// Getters for activity fields
char* getDeadline(activity a) {
    return a->deadline;
}

char* getDescr(activity a) {
    return a->description;
}

char* getCourse(activity a) {
    return a->course;
}

int getWorkedHours(activity a) {
    return a->timeSpentAct;
}

int getTimeReq(activity a) {
    return a->estimatedActTime;
}

priority getP(activity a) {
    return a->p;
}

c_state getState(activity a) {
    return a->state;
}

char* getCreatedDate(activity a) {
    return a->created;
}

// Set the creation date for the activity
void setCreatedDate(activity a, const char* date) {
    strncpy(a->created, date, sizeof(a->created));
    a->created[10] = '\0'; // Ensure null-termination
}

// Convert priority enum value to string
char* priorityToStr(int p) {
    switch (p) {
        case 1: return "Low";
        case 2: return "Medium";
        case 3: return "High";
        default: return "-";
    }
}

// Print a summary of the activity
void printAct(activity a) {
    const char *states[] = {"Uncompleted", "Ongoing", "Completed"};
    printf("Activity: %s | Course: %s | Deadline: %s | Created: %s | Priority: %s | State: %s\n",
           a->description, a->course, a->deadline, a->created,
           priorityToStr(a->p), states[a->state]);
}

// Convert a string date in YYYY-MM-DD format to a time_t object
time_t dataConvert(char* data_str) {
    int y, m, d;
    sscanf(data_str, "%d-%d-%d", &y, &m, &d);
    struct tm tm = {0};
    tm.tm_year = y - 1900;
    tm.tm_mon = m - 1;
    tm.tm_mday = d;
    return mktime(&tm);
}

// Check if the activity is overdue (not completed and deadline has passed)
int isLate(activity a) {
    if (getState(a) == COMPLETED)
        return 0;
    time_t deadline = dataConvert(getDeadline(a));
    time_t today = time(NULL);
    return difftime(today, deadline) > 0;
}
