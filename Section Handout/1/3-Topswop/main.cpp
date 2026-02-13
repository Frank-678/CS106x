static int getTopswopNumber(Stack<int> s) {
    Queue<int> swap;
    int times = 0;
    while (s.peek() != 1) {
        // out
        int k = s.peek();
        for (int i = 1; i <= k; i++) {
            swap.enqueue(s.pop());
        }

        // in
        for (int i = 1; i <= k; i++) {
            s.push(swap.dequeue());
        }

        times++;
    }
    return times;
}