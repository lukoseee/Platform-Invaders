#include "test.hpp"

// global variables
Test_Function* functions = NULL;
Test_Function beforeEach = NULL;
int functionCount = 0;
int checkCount = 0;

void setBeforeEach(Test_Function function) {
    beforeEach = function;
}

void addTest(Test_Function function) {
    functionCount++;
    functions = (Test_Function*)realloc(functions, sizeof(Test_Function) * functionCount); // dynamic realloc
    functions[functionCount - 1] = function;
}

void runTests() {
    // ensure good printf formatting
    printf("\n");
    for(int i = 0; i < functionCount; i++){
        printf("Running Test %d\n", i + 1);

        if(beforeEach)
            beforeEach();

        checkCount = 0;
        (*functions[i])();
    }
    printf("Tests Complete.\n\n");
}

void cleanTests() {
    free(functions);
}

void check(bool result) {
    checkCount++;
    if(result)
        printf("\tcheck %d passed\n", checkCount);
    else
        printf("\tcheck %d failed\n", checkCount);
}