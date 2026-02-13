/*
 * File: test_generate_story.cpp
 * -----------------------------
 * Rigorous test suite for generateStory function.
 * Covers 20 distinctive scenarios.
 */

#include <iostream>
#include <string>
#include <iomanip>
#include "console.h"
#include "map.h"
#include "vector.h"
#include "simpio.h"
using namespace std;

// --- 待测函数 (你的严谨实现) ---
static string generateStory(const string& storyTemplate, const Map<string, string>& data) {
    string result = "";
    for (int i = 0; i < storyTemplate.length(); ++i) {
        if (storyTemplate[i] != '{') {
            result += storyTemplate[i];
        } else {
            int m = i + 1;
            string token = "";
            while (storyTemplate[m] != '}') {
                token += storyTemplate[m];
                m++;
            }
            result += data[token];
            i = m;
        }
    }
    return result;
}

// --- 测试辅助工具 ---
void runTest(int id, const string& desc, const string& tmpl,
             const Map<string, string>& map, const string& expected) {
    string actual = generateStory(tmpl, map);
    bool pass = (actual == expected);

    cout << "Test " << setw(2) << id << " [" << desc << "]: ";
    if (pass) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
        cout << "   Expected: \"" << expected << "\"" << endl;
        cout << "   Actual:   \"" << actual << "\"" << endl;
    }
}

int main() {
    // 1. 构建全量测试数据环境 (Comprehensive Context)
    Map<string, string> context;
    // 基础数据
    context.put("name", "Frank");
    context.put("action", "coded");
    context.put("lang", "C++");
    // Handout 案例数据
    context.put("actor", "Mike Vernal");
    context.put("restaurant", "The French Laundry");
    context.put("rating", "5");
    context.put("friend", "Jessie Duan");
    context.put("band", "Green Day");
    context.put("app", "Spotify");
    // 边缘情况数据
    context.put("empty", "");          // 空值
    context.put("space", " ");         // 空格值
    context.put("symbol", "#&@!");     // 特殊符号
    context.put("long", "supercalifragilisticexpialidocious"); // 长词
    context.put("num", "106");         // 数字
    context.put("a", "A");             // 单字符键值
    context.put("b", "B");

    cout << boolalpha; // 让 bool 输出 true/false 而非 1/0

    // --- 20个严谨测试用例 ---

    // [Group 1: 基础逻辑]
    // Case 1: 无 Token (纯文本)
    runTest(1, "No tokens", "Hello World", context, "Hello World");

    // Case 2: 空字符串
    runTest(2, "Empty string", "", context, "");

    // Case 3: 仅有一个 Token (全匹配)
    runTest(3, "Full token", "{name}", context, "Frank");

    // [Group 2: 位置测试]
    // Case 4: Token 在开头
    runTest(4, "Token at start", "{name} is here.", context, "Frank is here.");

    // Case 5: Token 在结尾
    runTest(5, "Token at end", "Written by {name}", context, "Written by Frank");

    // Case 6: Token 在中间
    runTest(6, "Token in middle", "I {action} today.", context, "I coded today.");

    // [Group 3: 复杂组合]
    // Case 7: 多个不同 Token
    runTest(7, "Multiple tokens", "{name} {action} {lang}.", context, "Frank coded C++.");

    // Case 8: 重复 Token (Repeated Keys)
    runTest(8, "Repeated tokens", "{name} likes {name}", context, "Frank likes Frank");

    // Case 9: 相邻 Token (无空格分割) - 测试 i=m 的逻辑是否严谨
    runTest(9, "Adjacent tokens", "{a}{b}", context, "AB");

    // [Group 4: 标点与格式]
    // Case 10: Token 紧贴标点 (前)
    runTest(10, "Punctuation before", "Hello, {name}!", context, "Hello, Frank!");

    // Case 11: Token 紧贴标点 (后) - 文档案例格式 "{rating}-star"
    runTest(11, "Punctuation after", "A {rating}-star review", context, "A 5-star review");

    // Case 12: Token 被括号包裹 (非Token定界符)
    runTest(12, "Brackets around", "({name})", context, "(Frank)");

    // [Group 5: Map 值的内容边界]
    // Case 13: Map 值为数字字符串
    runTest(13, "Numeric value", "Room {num}", context, "Room 106");

    // Case 14: Map 值为特殊符号
    runTest(14, "Symbol value", "Password: {symbol}", context, "Password: #&@!");

    // Case 15: Map 值为超长字符串 (Buffer check)
    runTest(15, "Long value", "Word: {long}", context, "Word: supercalifragilisticexpialidocious");

    // Case 16: Map 值为空字符串 (Empty replacement)
    runTest(16, "Empty value", "Value is [{empty}]", context, "Value is []");

    // Case 17: Map 值为仅空格
    runTest(17, "Space value", "Gap[{space}]Gap", context, "Gap[ ]Gap");

    // [Group 6: 单词内部替换]
    // Case 18: Token 嵌入单词内部 (Prefix/Suffix)
    runTest(18, "Embedded token", "Un{empty}believable", context, "Unbelievable");

    // [Group 7: 文档真实案例复现]
    // Case 19: Handout Problem 2 Example 1
    runTest(19, "Handout Ex 1", "{friend} accepted your friend request.", context,
            "Jessie Duan accepted your friend request.");

    // Case 20: Handout Problem 2 Example 5
    runTest(20, "Handout Ex 5", "{actor} gave {restaurant} a {rating}-star review.", context,
            "Mike Vernal gave The French Laundry a 5-star review.");

    return 0;
}
