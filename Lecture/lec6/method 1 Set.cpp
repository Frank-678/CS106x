// https://www.codestepbystep.com/r/problem/view/cpp/splcollections/set/isHappyNumber

bool f(int n, Set<int>& checked);

bool isHappyNumber(int n) {
    Set<int> checked;
    return f(n, checked);
}

bool f(int n, Set<int>& checked) {
    checked.add(n);
    string s = integerToString(n);
    int sum = 0;
    for (int i = 0; i < s.length(); ++i) {
        int p = charToInteger(s[i]);
        sum += p * p;
    }
    
    if (sum == 1) {
        return true;
    } else if (!checked.contains(sum)) {
        return f(sum, checked);
    } else if (checked.contains(sum)) {
        return false;
    }

    return false;
}
