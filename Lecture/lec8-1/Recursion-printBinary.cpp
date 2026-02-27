// 这确实是一个看似基础却体现思路的重要性的题！Tricky！

void printBinary(int n) {
    if (n < 0) {
        cout << "-";
        printBinary(-n);
    } else if (n <= 1) {
        cout << n;
    } else {
        int lastdigit = n % 2;
        int rest = n / 2;
        printBinary(rest);
        printBinary(lastdigit);
    }
}



