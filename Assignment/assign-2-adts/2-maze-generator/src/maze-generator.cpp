/**
 * File: maze-generator.cpp
 * ------------------------
 * Presents an adaptation of Kruskal's algorithm to generate mazes.
 */

#include <iostream>
#include <string>
using namespace std;

#include "console.h"
#include "simpio.h"
#include "set.h"

#include "maze-graphics.h"
#include "maze-types.h"


static int getMazeDimension(string prompt,
                            int minDimension = 7, int maxDimension = 50) {
    while (true) {
        int response = getInteger(prompt);
        if (response == 0) return response;
        if (response >= minDimension && response <= maxDimension) return response;
        cout << "Please enter a number between "
             << minDimension << " and "
             << maxDimension << ", inclusive." << endl;
    }
}

void initInternal(int dimention, Set<cell>& cells, Set<wall>& walls) {
    for (int i = 0; i < dimention; ++i) {
        for (int j = 0; j < dimentionl ++j) {
            cell c {i, j};
            cells.add(c);
        }
    }

    for (const cell& c1 : cells) {
        for (const cell& c2 : cells) {
            if (c1.row == c2.row && c2.col - c1.col == 1
                || c1.col == c2.col && c2.row - c1.row == 1) {
                wall w {c1, c2};  // c1左/上于c2
                walls.add(w);
            }
        }
    }
}

void randomRemove(int dimention, Set<cell>& cells, Set<wall>& walls) {
    for (const cell& c1 : cells) {
        for (const cell& c2 : cells) {
            if (!walls.contain({c1, c2})) {
                Set<cell> chamber {c1, c2};
            }


        }
    }
}

void render(int dimention, MazeGeneratorView& display){
    display.MazeGeneratorView();
    display.setDimension(dimention);
    display.drawBorder();
}

int main() {
    while (true) {
        int dimension = getMazeDimension("What should the dimension of your maze be [0 to exit]? ");
        if (dimension == 0) break;
        cout << "This is where I'd animate the construction of a maze of dimension " << dimension << "." << endl;

        Set<cell> cells;
        Set<wall> walls;
        initInternal(dimension, cells, walls);

        randomRemove(dimension, cells, walls);

        MazeGeneratorView display;
        render(dimension, display);
        display.repaint();
    }

    return 0;
}

