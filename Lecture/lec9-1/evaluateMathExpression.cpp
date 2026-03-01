// https://www.codestepbystep.com/r/problem/view/cpp/recursion/evaluateMathExpression

// (1+((2*3)+1)) 任何的两数运算都有括号
//  ^
// ((2)+(3))
// 写函数先思考：What SHOULD it do? 这样写递归会更得心应手
int evalHelper(const string& exp, int& index) {
    if (isdigit(exp[index])) {    // base case
        int result = exp[index] - '0';
        index++;
        return result;
    } else { // if (exp[index] == '(') {
        // recursive case
        index++; // skip
        int left = evalHelper(exp, index); // 我们的目的定为index跳过')'
        char op = exp[index++];
        int right = evalHelper(exp, index);
        index++; // skip  // 是否会index溢出？cpp string capacity > size

        switch (op) {
            case '+': return left + right;
            case '*': return left * right;
        }
    }
    error("Invalid Math Expression.");
}



int evaluateMathExpression(const string& exp) {
    int index = 0;
    return evalHelper(exp, index);
}