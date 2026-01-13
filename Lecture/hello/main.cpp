// hello.cpp
#include "console.h"
#include <iostream>
#include "simpio.h"
using namespace std;

int main() {    // 在 C++ 中等同于 int f(void)。它表示该函数不接受任何参数。[C语言不同，表示传递任意参数]
    // cout << "Your age: ";
    // int age;
    // cin >> age;
    int age = getInteger("How old are you? ");
    cout << "Hello, World!" << endl;
    cout << "You are " << age << " years old" << endl;
    return 0;
}
