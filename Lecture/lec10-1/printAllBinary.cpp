// https://www.codestepbystep.com/r/problem/view/cpp/backtracking/printAllBinary
#include <iostream>
#include <string>
using namespace std;

// 最关键：选择与探索，直到无可选择
// 补充参数prefix：类似于lec8-3 crawl (directory under directory).cpp 中的缩放问题
// 但在这里，prefix有另一层意义：记录选择！
void printAllBinary(int digits, string prefix = "") {
    if (digits == 0) {
        // if there's nothing to choose, print what they chose.
        cout << prefix <<endl;
    } else if (digits > 0) {
        // recursive case
        printAllBinary(digits - 1, prefix + "0");
        printAllBinary(digits - 1, prefix + "1");
        
    }
}

int main() {
    printAllBinary(4);
    return 0;
}
