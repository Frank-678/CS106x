// 这确实是一个看似基础却体现思路的重要性的题！Tricky！
#include <iostream>
#include "console.h"
#include "simpio.h"
#include "timer.h"
using namespace std;

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

int main() {
    while (true) {
        int number = getInteger("Decimal number: ");

        for (int var = 0; var < 10; ++var) {
            Timer tim;
            tim.start();
            printBinary(number);
            cout << endl;
            tim.stop();
            cout << "The code took " << tim.elapsed() << "ms to finish." << endl;
        }
    }
    return 0;
}

