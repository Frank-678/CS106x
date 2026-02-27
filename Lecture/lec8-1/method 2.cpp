// 方法二：使用位遮挡 & 1<<x 便可以从左往右判断每一位

void printBrinary(int n) {
    unsigned int mask = 1;
    while (mask < n) mask <<= 1;
}