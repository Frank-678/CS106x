void reverseLines(ifstream& input) {
    string line;
    if (!getline(input, line)) {
        // base case
        // nothing to do (or say: return; or say: ;)
    } else {
        reverseLines(input); // & so the same one input “读位置”（cursor / get pointer）
        cout << line << endl;
    }
} 