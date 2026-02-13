static string infixToPostfix(const string& infix) {
    string postfix = "";
    Stack<char> s;
    for (char ch : infix) {
        if (isdigit(ch)) {
            postfix += ch;
        } else if (ch == '(') {
            s.push(ch);
        } else if (ch == ')') {
            while (s.peek() != '(') {
                postfix += s.pop();
            }
            s.pop();
        } else if (ch == '+') {
            if (!s.isEmpty() && (s.peek() == '*' || s.peek() == '+')) {
                postfix += s.pop();
            }
            s.push(ch);
        } else if (ch == '*') {
            if (!s.isEmpty() && s.peek() == '*') {
                postfix += s.pop();
            }
            s.push(ch);
        }
    }

    while (!s.isEmpty()) {
        postfix += s.pop();
    }

    return postfix;
}