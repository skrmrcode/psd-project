#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"
#include "activity.h"
#include "heap.h"

FILE* resultFile;  // File to store test results

// Log the result of a test case
void log_test_result(const char* testname, int condition) {
    if (condition) {
        fprintf(resultFile, "[PASS] %s\n", testname);
    } else {
        fprintf(resultFile, "[FAIL] %s\n", testname);
    }
}

// Test case: creation of a valid activity
void test_insert_activity() {
    activity a = newAct("Study math", "Calculus 1", "2025-06-15", 10, MEDIUM);
    int passed = strcmp(getDescr(a), "Study math") == 0 &&
                 strcmp(getCourse(a), "Calculus 1") == 0 &&
                 strcmp(getDeadline(a), "2025-06-15") == 0 &&
                 getWorkedHours(a) == 0 &&
                 getState(a) == UNCOMPLETED &&
                 getP(a) == MEDIUM;
    log_test_result("Insert valid activity", passed);
}

// Test case: updating progress of an activity
void test_update_progress() {
    activity a = newAct("Study physics", "Physics 2", "2025-06-20", 5, HIGH);
    updateProgress(a, 2);
    int partial = getWorkedHours(a) == 2 && getState(a) == ONGOING;
    updateProgress(a, 3);
    int complete = getWorkedHours(a) == 5 && getState(a) == COMPLETED;
    log_test_result("Partial progress update", partial);
    log_test_result("Complete progress update", complete);
}

// Test case: generating and validating a report
void test_generate_report() {
    heap h = newHeap(10);
    activity a1 = newAct("Study chemistry", "Chemistry", "2025-06-10", 4, LOW);
    activity a2 = newAct("Study literature", "Literature", "2025-06-12", 3, HIGH);
    updateProgress(a2, 3); // Mark as completed

    addAct(h, a1);
    addAct(h, a2);

    FILE *f = fopen("report_test.txt", "w");
    if (!f) {
        log_test_result("Report file creation", 0);
        return;
    }

    for (int i = 0; i < getNumElem(h); i++) {
        activity a = getActivity(h, i);
        if (getState(a) == COMPLETED)
            fprintf(f, "[COMPLETED] ");
        else if (isLate(a))
            fprintf(f, "[OVERDUE] ");
        else
            fprintf(f, "[ONGOING] ");

        fprintf(f, "%s|%s|%s|%d hours spent\n", getDescr(a), getCourse(a), getDeadline(a), getWorkedHours(a));
    }

    fclose(f);

    f = fopen("report_test.txt", "r");
    if (!f) {
        log_test_result("Read report file", 0);
        return;
    }

    char line[512];
    int count = 0;
    while (fgets(line, sizeof(line), f)) count++;
    fclose(f);

    log_test_result("Check report line count", count == 2);
}

// Entry point for running all tests
int main() {
    resultFile = fopen("result.txt", "w");
    if (!resultFile) {
        printf("Error opening result.txt!\n");
        return 1;
    }

    test_insert_activity();
    test_update_progress();
    test_generate_report();

    fprintf(resultFile, "\nAll tests completed.\n");
    fclose(resultFile);
    return 0;
}
