int sumOfSquares(int n) {
    string s = integerToString(n); 
    int sum = 0;
    for (int i = 0; i < s.length(); ++i) {
        int p = charToInteger(s[i]);
        sum += p * p;
    }
    return sum;
}

bool isHappyNumber(int n) {
    int slow = n;
    int fast = n;
    while(true) {
        fast = sumOfSquares(sumOfSquares(fast));
        slow = sumOfSquares(slow);

        if (slow == 1) return true;
        if (slow == fast) return false;
    }
    return false;
}
