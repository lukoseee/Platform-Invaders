#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef void (*Test_Function)();

void setBeforeEach(Test_Function); // define a function to be called before all tests
void addTest(Test_Function); // add a function to be run as a test
void runTests(); // run all added tests
void cleanTests(); // free memory
void check(bool); // pass a boolean you want to test