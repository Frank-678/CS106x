// https://www.codestepbystep.com/r/problem/view/cpp/strings/nameDiamond

//#include "console.h"
#include <iostream>
#include <string>
using namespace std;

void nameDiamond(string s);

int main(void) {
    string s = "Hello";
    string t = "<world";
    if (s > t) {
        cout << s.at(0) << (int) t[0] << (s > t) * 8 << endl;
    }

    // Magic number
    cout << "no position is " << std::basic_string<char>::npos << endl; // 如果不加endl，这行文字通常会先进入 cout 的缓冲区，不一定立刻“送到”IDE的输出窗口。而在 Qt Creator 的 Application Output 这种“被重定向的标准输出”场景下，stdout 往往是 全缓冲 或者 按行（遇到换行才更新），所以没有换行就不显示/不更新，看起来就像“没输出”。（程序结束时理论上会刷新，但 IDE 的显示机制常常是“等到一行完整/等到 flush 才更新”，所以你会觉得它没输出。）

    nameDiamond(s);
    return 0;
}

void nameDiamond(string s) {
    cout << endl;
    for (int j = 1; j <= s.length(); j++) {
        cout << s.substr(0, j) << endl;
    }
    for (int j = 1; j < s.length(); j++) {
        cout << string(j, ' ') << s.substr(j) << endl;
    }
}
