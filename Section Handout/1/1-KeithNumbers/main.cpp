// https://www.codestepbystep.com/r/problem/view/cpp/splcollections/vector/isKeithNumber

bool isKeithNumber(int n) {
    string s = integerToString(n);
    Vector<int> v;
    for (char c : s) {
        v.add(charToInteger(c));
    }
    int k = v.size();  // 位数

    for (int p = k; ; p++) {
        int sum = 0;
        for (int i = 0; i < k; ++i) {
            sum += v[p - i - 1];
        }
        v.add(sum);

        if (sum == n) {
            return true;
        } else if (sum > n) {
            return false;
        }
    }
}
