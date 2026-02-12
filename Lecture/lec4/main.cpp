#include <iostream>
#include <string>
#include "Vector.h"
using namespace std;

// 1
void removeAll(Vector<string>& words, string del) {
    for (int var = words.size() - 1; var >= 0; --var) {
        if (words[var] == del) {
            words.remove(var);
        }
    }
}

//2
void removeAll(Vector<string>& words, string del) {
    for (int var = 0; var < words.size(); ++var) {
        if (words[var] == del) {
            words.remove(var);
            --var;
        }
    }
}

//3
void removeAll(Vector<string>& words, string del) {
    for (int var = 0; var < words.size(); ++var) {
        while (var < words.size() && words[var] == del) {
            words.remove(var);
        }
    }
}

int main(void) {
    Vector<string> s {"hello", "a", "b", "c", "b"};
    removeAll(s, "b");
    cout << s << endl;

    return 0;
}
