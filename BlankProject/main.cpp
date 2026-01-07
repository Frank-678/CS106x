// hello.cpp
#include "console.h"
#include <iostream>
#include "simpio.h"
using namespace std;

int main(void) {
    // cout << "Your age: ";
    // int age;
    // cin >> age;
    int age = getInteger("How old are you? ");
    cout << "Hello, World!" << endl;
    cout << "You are " << age << " years old" << endl;
    return 0;
}
