bool isPalindrome(string s) {
    int l = s.length();
    if (l == 0 || l == 1) {
        return true;
    } else if (tolower(s[0]) == tolower(s[l - 1])) {
        return isPalindrome(s.substr(1, l - 2));
    } else {
        return false;
    }
}
