/*
 * File: main.cpp
 * --------------
 * Blank C++ project configured to use Stanford cslib and Qt
 */

#include "console.h"
#include "simpio.h"
#include "vector.h"
#include "error.h"
#include "SimpleTest.h" // IWYU pragma: keep (needed to quiet spurious warning)
using namespace std;


int main()
{
    if (runSimpleTests(SELECTED_TESTS)) {
        return 0;
    }

    string name = getLine("What is your name?");
    cout << "Hello, " << name << endl;
    return 0;
}

double avgVec(Vector<int>vec) {
    if (vec.size() == 0) {
        error("Cannot find the average of a zero-element vector!");
    }
    int sum = 0;
    for (int i : vec) {
        sum += i;
    }
    return sum / vec.size();
}

PROVIDED_TEST("Test avgVec function on short vector of integers.") {
    Vector<int> v = {1, 5, 7, 11, 22, 33, 100, 9, 0};
    EXPECT_EQUAL(avgVec(v), 20.0);
}

STUDENT_TEST("My test of avgVec with a zero-element vector") {
    Vector<int> v = {};
    EXPECT_ERROR(avgVec(v));
}


