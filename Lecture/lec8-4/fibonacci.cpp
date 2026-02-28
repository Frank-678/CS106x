int fib(int n) {
    // base case
    if (n == 0) return 0;
    if (n == 1) return 1;

    // recursive case
    return fib(n - 1) + fib(n - 2);
}


// 通过https://www.codestepbystep.com/r/problem/view/cpp/loops/fibonacci测试
// void fibonacci(int max) {
//     cout << "Fibonacci sequence up to "<< max << ":" << endl;

//     for (int i = 0; ; i++) {
//         int n = fib(i);

//         if (n >= max) break;
//         cout << n << endl;
//     }
// }