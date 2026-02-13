/*
 * File: test_shunting_yard.cpp
 * ----------------------------
 * Rigorous test suite for infixToPostfix function.
 * Validates precedence, associativity, and parentheses handling.
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include "console.h"
#include "stack.h"
#include "simpio.h"
#include "strlib.h"
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

// --- 待测函数原型 (请在此处或上方填入你的实现) ---
static string infixToPostfix(const string& infix);

/* * 你的实现代码应该放在这里。
 * 为了演示，这里留空。
 * static string infixToPostfix(const string& infix) { ... }
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

// --- 测试执行工具 ---
void runTest(int id, const string& desc, const string& infix, const string& expected) {
    string actual = infixToPostfix(infix);
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
        cout << "   [Input]:    \"" << infix << "\"" << endl;
        cout << "   [Expected]: \"" << expected << "\"" << endl;
        cout << "   [Actual]:   \"" << actual << "\"" << endl;
    }
}

int main() {
    cout << "--- Shunting-Yard Test Suite ---" << endl;

    // [Group 1: 基础原子操作]
    // Case 1: 单个数字 (Base case)
    runTest(1, "Single digit", "1", "1");

    // Case 2: 简单加法
    runTest(2, "Simple Add", "1+2", "12+");

    // Case 3: 简单乘法
    runTest(3, "Simple Mul", "3*4", "34*");

    // [Group 2: 优先级测试 (Precedence)]
    // Case 4: 乘法在后 (Add then Mul) -> 1+(2*3) -> 123*+
    runTest(4, "Precedence 1+2*3", "1+2*3", "123*+");

    // Case 5: 乘法在前 (Mul then Add) -> (1*2)+3 -> 12*3+
    runTest(5, "Precedence 1*2+3", "1*2+3", "12*3+");

    // Case 6: 混合交替 -> 1*2+3*4 -> (1*2)+(3*4) -> 12*34*+
    runTest(6, "Mixed Ops", "1*2+3*4", "12*34*+");

    // [Group 3: 左结合律 (Left Associativity)]
    // Case 7: 连续加法 -> (1+2)+3 -> 12+3+
    runTest(7, "Left Assoc Add", "1+2+3", "12+3+");

    // Case 8: 连续乘法 -> (2*3)*4 -> 23*4*
    runTest(8, "Left Assoc Mul", "2*3*4", "23*4*");

    // Case 9: 长链混合 -> 1+2+3*4 -> 12+34*+
    runTest(9, "Long Chain", "1+2+3*4", "12+34*+");

    // [Group 4: 括号测试 (Parentheses)]
    // Case 10: 简单括号改变优先级 -> (1+2)*3 -> 12+3*
    // Source [91]
    runTest(10, "Parens (1+2)*3", "(1+2)*3", "12+3*");

    // Case 11: 括号在后 -> 1*(2+3) -> 123+*
    runTest(11, "Parens 1*(2+3)", "1*(2+3)", "123+*");

    // Case 12: 冗余括号 -> ((1+2)) -> 12+
    runTest(12, "Redundant Parens", "((1+2))", "12+");

    // Case 13: 括号内包含高优先级 -> (1+2*3) -> 123*+
    runTest(13, "Parens Mixed", "(1+2*3)", "123*+");

    // [Group 5: 文档案例复现 (Handout Examples)]
    // Case 14: Handout Ex 1
    runTest(14, "Handout Ex 3+6", "3+6", "36+");

    // Case 15: Handout Ex 3 (Modified strict)
    // Handout: 1+3+1+1*3 -> 13+1+13*+
    runTest(15, "Handout Ex Long", "1+3+1+1*3", "13+1+13*+");

    // Case 16: Handout Ex 4
    // 4*(1+3)*(6+4+2) -> 413+*64+2+*
    // Logic: 4 * (4) * (12) -> 4 4 * 12 * -> 4 1 3 + * 6 4 + 2 + *
    // 验证 Source 96 的输出: 413+*64+2+*
    runTest(16, "Handout Complex (Fixed)", "4*(1+3)*(6+4+2)", "413+*64+2+*");

    // [Group 6: 深度嵌套与边界]
    // Case 17: 嵌套括号 -> (1+(2*3)) -> 123*+
    runTest(17, "Nested Parens", "(1+(2*3))", "123*+");

    // Case 18: 全括号结构 -> (1+2)*(3+4) -> 12+34+*
    runTest(18, "Full Parens", "(1+2)*(3+4)", "12+34+*");

    // Case 19: 括号位于中间 -> 1+(2+3)*4 -> 123+4*+
    runTest(19, "Mid Parens", "1+(2+3)*4", "123+4*+");

    // Case 20: 复杂结合 -> 1*2*3+4*5*6 -> 12*3*45*6*+
    runTest(20, "Complex Assoc", "1*2*3+4*5*6", "12*3*45*6*+");

    return 0;
}
