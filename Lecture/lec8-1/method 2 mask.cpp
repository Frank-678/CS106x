// 方法二：使用位遮挡 & 1<<x 便可以从左往右判断每一位 
#include <iostream>
using namespace std;

void printBinary(int n) {
    if (n < 0) {
        cout << '-';
        n *= -1;
    }

    unsigned int un = (unsigned int)n;

    unsigned int mask = 1;
    while ((mask << 1) <= un) mask <<= 1;  // 先位移后判断！（如果n小于1<<x（x+1位）那么必然只有x位）

    for (; mask; mask >>= 1) cout << ((un & mask) ? 1 : 0);
    cout << endl;
}

int main() {
    while (true) {
        int n;
        cin >> n;
        printBinary(n);
    }
}