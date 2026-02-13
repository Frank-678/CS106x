// https://www.codestepbystep.com/r/problem/view/cpp/splcollections/stackqueue/mirror

void mirror(Queue<string>& q) {
    Stack<string> s;
    int l = q.size();
    for (int i = 0; i < l; ++i) {
        s.push(q.dequeue());
        q.enqueue(s.peek());
    }
    while (!s.isEmpty()) {
        q.enqueue(s.pop());
    }    
}
