// https://www.codestepbystep.com/r/problem/view/cpp/splcollections/stackqueue/stutter

void stutter(Queue<int>& q) {
    int l = q.size();
    for (int i =0;i<l;++i) {
        int temp = q.dequeue();
        q.enqueue(temp);
        q.enqueue(temp);
    }
}



