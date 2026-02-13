#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "stack.h"
using namespace std;

int checkBalance(const string code) {
    Stack<char> s;
    int l = code.length();
    for (int i = 0; i < l; ++i) {
        if (code[i] == '(' || code[i] == '{') {
            s.push(code[i]);
        } else if (code[i] == ')') {
            if (s.isEmpty() || s.pop() != '(') {
                return i;
            }
        } else if (code[i] == '}') {
            if (s.isEmpty() || s.pop() != '{') {
                return i;
            }
        }
    }
    if (!s.isEmpty()) {
        return l;
    }
    return -1;
}

int main() {
    string code = getLine("Your code: ");
    cout << checkBalance(code) << endl;
    return 0;
}
