#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include "console.h"
#include "simpio.h"
#include "set.h"
#include "vector.h"
#include "random.h"
#include "maze-graphics.h"
#include "maze-types.h"

using namespace std;

int findChamber(Vector<Set<cell>>& chambers, cell c) {
    for (int i = 0; i < chambers.size(); i++) {
        if (chambers[i].contains(c)) return i;
    }
    return -1;
}

int main() {
    MazeGeneratorView view;
    while (true) {
        int n = getInteger("Dimension (0 to exit): ");
        if (n <= 0) break;

        view.setDimension(n);
        view.drawBorder();

        Vector<wall> walls;
        Vector<Set<cell>> chambers;

        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                Set<cell> s;
                s.add({r, c});
                chambers.add(s);

                if (r < n - 1) walls.add({{r, c}, {r + 1, c}});
                if (c < n - 1) walls.add({{r, c}, {r, c + 1}});
            }
        }

        view.addAllWalls(walls);
        view.repaint();

        // 创建一个随机数生成器 mt
        static std::mt19937 mt(0);
        // 调用标准库的 3 参数 shuffle
        std::shuffle(walls.begin(), walls.end(), mt);

        for (wall w : walls) {
            int i1 = findChamber(chambers, w.one);
            int i2 = findChamber(chambers, w.two);

            if (i1 != i2) {
                view.removeWall(w);
                view.repaint();
                chambers[i1] += chambers[i2];
                chambers.remove(i2);
            }
        }
    }
    return 0;
}
