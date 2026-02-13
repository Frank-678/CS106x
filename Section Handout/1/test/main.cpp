/*
 * File: test_story.cpp
 * --------------------
 * A test harness for the generateStory function.
 */

#include <iostream>
#include <string>
#include "console.h" // Stanford library header
#include "map.h"     // Stanford library header
#include "vector.h"  // Stanford library header
using namespace std;

// 函数原型声明
static string generateStory(const string& storyTemplate, const Map<string, string>& data);

int main() {
    // 1. 构建测试数据 (Data Map)
    Map<string, string> context;
    context.put("name", "Jessie Duan");
    context.put("band", "Green Day");
    context.put("application", "Spotify");
    context.put("actor", "Mike Vernal");
    context.put("restaurant", "The French Laundry");
    context.put("rating", "5");
    context.put("title", "Because Faiz told me to");
    context.put("target", "Jeffrey Spehar");

    // 2. 定义测试用例 (Test Cases)
    Vector<string> templates;

    // Case 1: 简单单变量 [cite: 22]
    templates.add("{name} accepted your friend request.");

    // Case 2: 多变量混合文本 [cite: 23]
    templates.add("{name} is listening to {band} on {application}.");

    // Case 3: 变量位于句中和句尾 [cite: 26]
    templates.add("{actor} gave {restaurant} a {rating}-star review.");

    // Case 4: 紧凑格式测试
    templates.add("Title:{title}");

    // 3. 执行测试与输出验证
    cout << "--- Begin Test ---" << endl;

    for (string t : templates) {
        string result = generateStory(t, context);
        cout << "Template: " << t << endl;
        cout << "Result:   " << result << endl;
        cout << "------------------" << endl;
    }

    return 0;
}

/*
 * Implementation of generateStory
 * Logic: Linear scan with state jump.
 */
static string generateStory(const string& storyTemplate, const Map<string, string>& data) {
    string result = "";
    for (int i = 0; i < storyTemplate.length(); ++i) {
        if (storyTemplate[i] != '{') {
            result += storyTemplate[i];
        } else {
            // 定位 Token 边界
            int m = i + 1;
            string token = "";
            while (storyTemplate[m] != '}') {
                token += storyTemplate[m];
                m++;
            }
            // 查表替换 (Const-safe access)
            // 注意：Stanford CPPLib Map 使用 get() 读取 const 引用
            result += data.get(token);

            // 索引同步：将 i 移动到 '}' 的位置
            // 下一轮循环的 ++i 将使其指向 '}' 后的第一个字符
            i = m;
        }
    }
    return result;
}
