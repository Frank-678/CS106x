#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "stack.h"
using namespace std;

int check(const string code) {
    Stack<char> s;
    int l = code.length();
    for (int i = 0; i < l; ++i) {
        if (code[i] == '(' || code[i] == '{') {
            s.push(code[i]);
        } else if (code[i] == ')') {
            if (!s.isEmpty()) {
                if (s.pop() != '(') {
                    return i;
                }
            } else {
                return i;
            }
        } else if (code[i] == '}') {
            if (!s.isEmpty()) {
                if (s.pop() != '{') {
                    return i;
                }
            } else {
                return i;
            }
        }
    }

    if (!s.isEmpty()) {
        return l;
    }
    return -1;
}

int main(void) {
    string code = getLine("Your code: ");
    cout << check(code) << endl;
    return 0;
}
