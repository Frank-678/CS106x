void printBinary(int n) {
    if (n == 0) {
        cout << 0;
    } else if (n == 1) {
        cout << 1;
    } else {
        int exp1;
        for (exp1 = 0; n > 1 << exp1; exp1++);
        int rest = n - (1 << exp1 - 1);
        int exp2;
        for (exp2 = 0; rest > 1 << exp2; exp2++);

        cout << 1;
        for (int i = 0; i < exp2 - exp1 +3; i++) {
            cout << 0;
        }

        printBinary(rest);
    }

}



