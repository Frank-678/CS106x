/*
 * File: test_topswop.cpp
 * ----------------------
 * Rigorous test suite for getTopswopNumber function.
 * Covers 20 distinctive scenarios ranging from trivial to complex.
 */

#include <iostream>
#include <string>
#include <iomanip>
#include "console.h"
#include "stack.h"
#include "vector.h"
#include "simpio.h"
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

// --- 待测函数原型 (请在此处或上方填入你的实现) ---
static int getTopswopNumber(Stack<int> s); 

/* * 你的实现代码应该放在这里，或者在测试运行前定义。
 * 为了演示，这里是一个空的占位符。
 * static int getTopswopNumber(Stack<int> s) { ... }
 */

// --- 辅助工具：控制台颜色 ---
void setConsoleColor(bool isSuccess) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, isSuccess ? 10 : 12); // 10=Green, 12=Red
#else
    if (isSuccess) std::cout << "\033[32m";
    else std::cout << "\033[31m";
#endif
}

void resetConsoleColor() {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
#else
    std::cout << "\033[0m";
#endif
}

// --- 辅助工具：构建栈 ---
// input: {2, 5, 1} means 2 is TOP, 1 is BOTTOM.
Stack<int> buildStack(Vector<int> nums) {
    Stack<int> s;
    // Stack is LIFO, so we push from the end of the vector to the beginning
    // so that index 0 becomes the top.
    for (int i = nums.size() - 1; i >= 0; i--) {
        s.push(nums[i]);
    }
    return s;
}

// --- 测试执行工具 ---
void runTest(int id, const string& desc, Vector<int> inputVec, int expected) {
    Stack<int> s = buildStack(inputVec);
    // 传入栈的副本，虽然函数签名通常是传值，这里确保测试框架侧也有备份（如果需要）
    int actual = getTopswopNumber(s); 
    bool pass = (actual == expected);

    cout << "Test " << setw(2) << id << ": ";
    
    setConsoleColor(pass);
    if (pass) {
        cout << "[PASS] True";
    } else {
        cout << "[FAIL] False";
    }
    resetConsoleColor();
    
    cout << ";" << endl;

    if (!pass) {
        cout << "   [Context]:  " << desc << endl;
        cout << "   [Input Top]: " << inputVec.toString() << endl;
        cout << "   [Expected]: " << expected << endl;
        cout << "   [Actual]:   " << actual << endl;
    }
}

int main() {
    cout << "--- Topswop Test Suite ---" << endl;

    // [Group 1: 基础/平凡情况]
    // Case 1: n=1, 已经在终态
    runTest(1, "Single element [1]", {1}, 0);

    // Case 2: n=2, 已经在终态
    runTest(2, "Sorted [1, 2]", {1, 2}, 0);

    // Case 3: n=3, 已经在终态
    runTest(3, "Sorted [1, 2, 3]", {1, 2, 3}, 0);

    // Case 4: n=2, 需要一次翻转
    // Stack: 2, 1 -> Top is 2. Invert 2 elems -> 1, 2. (1 step)
    runTest(4, "Simple swap [2, 1]", {2, 1}, 1);

    // [Group 2: n=3 排列组合]
    // Case 5: [2, 1, 3] -> Top 2, swap 2 -> [1, 2, 3] (1 step)
    runTest(5, "n=3 Case A", {2, 1, 3}, 1);

    // Case 6: [3, 2, 1] -> Top 3, swap 3 -> [1, 2, 3] (1 step)
    // 注意：这是完全逆序
    runTest(6, "Reverse n=3", {3, 2, 1}, 1);

    // Case 7: [2, 3, 1] -> 2,3,1 -> 3,2,1 -> 1,2,3 (2 steps)
    runTest(7, "n=3 Case B", {2, 3, 1}, 2);

    // Case 8: [3, 1, 2] -> 3,1,2 -> 2,1,3 -> 1,2,3 (2 steps)
    runTest(8, "n=3 Case C", {3, 1, 2}, 2);

    // [Group 3: Handout 经典案例]
    // Case 9: 文档中的例子
    // 2, 5, 1, 3, 4 -> (flip 2) -> 5, 2, 1, 3, 4 -> (flip 5) -> 4, 3, 1, 2, 5 
    // -> (flip 4) -> 2, 1, 3, 4, 5 -> (flip 2) -> 1, 2, 3, 4, 5. (Total 4)
    runTest(9, "Handout Example", {2, 5, 1, 3, 4}, 4);

    // [Group 4: n=4 的典型路径]
    // Case 10: 完全逆序 n=4
    // 4,3,2,1 -> 1,2,3,4 (1 step)
    runTest(10, "Reverse n=4", {4, 3, 2, 1}, 1);

    // Case 11: [2, 3, 4, 1]
    // -> 3,2,4,1 -> 4,2,3,1 -> 1,3,2,4 (3 steps)
    runTest(11, "n=4 Case A", {2, 3, 4, 1}, 3);

    // Case 12: [3, 4, 2, 1]
    // -> 2,4,3,1 -> 4,2,3,1 -> 1,3,2,4 (3 steps)
    runTest(12, "n=4 Case B", {3, 4, 2, 1}, 3);

    // Case 13: [4, 1, 2, 3]
    // -> 3,2,1,4 -> 1,2,3,4 (2 steps)
    runTest(13, "n=4 Case C", {4, 1, 2, 3}, 2);

    // [Group 5: n=5 及更大]
    // Case 14: 完全逆序 n=5
    runTest(14, "Reverse n=5", {5, 4, 3, 2, 1}, 1);

    // Case 15: [2, 3, 4, 5, 1] (循环移位)
    // -> 3,2,4,5,1 -> 4,2,3,5,1 -> 5,3,2,4,1 -> 1,4,2,3,5 (4 steps)
    runTest(15, "n=5 Cyclic Shift", {2, 3, 4, 5, 1}, 4);

    // Case 16: [5, 1, 2, 3, 4]
    // -> 4,3,2,1,5 -> 1,2,3,4,5 (2 steps)
    runTest(16, "n=5 Case A", {5, 1, 2, 3, 4}, 2);

    // Case 17: n=6 逆序
    runTest(17, "Reverse n=6", {6, 5, 4, 3, 2, 1}, 1);

    // [Group 6: 边界压力测试]
    // Case 18: n=10, 1 在第二位
    // [2, 1, 3, 4, 5, 6, 7, 8, 9, 10] -> 1, 2... (1 step)
    runTest(18, "n=10, 1 at pos 2", {2, 1, 3, 4, 5, 6, 7, 8, 9, 10}, 1);

    // Case 19: n=10, 1 在栈顶
    Vector<int> largeSorted;
    for(int i=1; i<=10; i++) largeSorted.add(i);
    runTest(19, "n=10 Sorted", largeSorted, 0);

    // Case 20: 复杂的 n=5
    // [3, 5, 4, 2, 1]
    // -> 4, 5, 3, 2, 1
    // -> 2, 3, 5, 4, 1
    // -> 3, 2, 5, 4, 1
    // -> 5, 2, 3, 4, 1
    // -> 1, 4, 3, 2, 5 (Total 5 steps)
    runTest(20, "n=5 Complex", {3, 5, 4, 2, 1}, 5);

    return 0;
}