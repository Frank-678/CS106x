// https://www.codestepbystep.com/r/problem/view/cpp/splcollections/set/isHappyNumber
bool isHappyNumber(int n) {
    string s = integerToString(n);
    int sum = 0;
    for (int i = 0; i < s.length(); ++i) {
        int p = charToInteger(s[i]);
        sum += p * p;
    }
    
    if (sum == 1) {
        return true;
    } else if (sum == 4 || !sum) {
        return false;
    } else {
        return isHappyNumber(sum);
    }

    return false;
}
