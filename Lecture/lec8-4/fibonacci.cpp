int fib(int n) {
    // base case
    if (n == 1 || n == 2) return 1;

    // recursive case
    return fib(n - 1) + fib(n - 2);
}