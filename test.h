#ifndef TEST_H
#define TEST_H

#include <stdio.h>

// External reference to the result file used for logging test outputs
extern FILE* resultFile;

// Log the result of a test case (prints [PASS] or [FAIL])
void log_test_result(const char* testname, int condition);

// Declaration of test functions
void test_insert_activity();
void test_update_progress();
void test_generate_report();

#endif
