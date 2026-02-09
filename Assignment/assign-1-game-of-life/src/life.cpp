/**
 * File: life.cpp
 * --------------
 * Implements the Game of Life.
 */

#include <iostream>  // for cout
#include <fstream> // for ifstream
#include <string> // for string
using namespace std;

#include "console.h" // required of all files that contain the main function
#include "filelib.h" // fileExists
#include "simpio.h"  // for getLine。
#include "grid.h" // for Grid
#include "strlib.h"

#include "life-constants.h"  // for kMaxAge, RANMIN and RANMAX
#include "life-graphics.h"   // for class LifeDisplay

void tailor(string choice, Grid<int>& currentAge, int& row, int& col);
void random(Grid<int>& currentAge, int& row, int& col);
void nextGen(Grid<int>& currentAge, Grid<int>& next, LifeDisplay& diagram);

/**
 * Function: welcome
 * -----------------
 * Introduces the user to the Game of Life and its rules.
 */
static void welcome() {
    cout << "Welcome to the game of Life, a simulation of the lifecycle of a bacteria colony." << endl;
    cout << "Cells live and die by the following rules:" << endl << endl;
    cout << "\tA cell with 1 or fewer neighbors dies of loneliness" << endl;
    cout << "\tLocations with 2 neighbors remain stable" << endl;
    cout << "\tLocations with 3 neighbors will spontaneously create life" << endl;
    cout << "\tLocations with 4 or more neighbors die of overcrowding" << endl << endl;
    cout << "In the animation, new cells are dark and fade to gray as they age." << endl << endl;
    getLine("Hit [enter] to continue....   "); // 有“enter to continue”的功能
}

/**
 * Function: getSleepTime
 * -----------------
 * Get a period of time to delay based on user's option
 */
int getSleepTime() {
    cout << "You choose how fast to run the simulation." << endl;
    cout << "\t1 = As fast as this chip can go!" << endl;
    cout << "\t2 = Not too fast, this is a school zone." << endl;
    cout << "\t3 = Nice and slow so I can watch everything that happens." << endl;
    cout << "\t4 = Require enter key be pressed before advancing to next generation." << endl;
    while (true) {
        int option = getInteger("Your choice: ");
        switch (option) {
        case 1:
            return 200;
        case 2:
            return 500;
        case 3:
            return 1500;
        case 4:
            return -1;
        default:
            cout << "Please enter a number between 1 and 4!" << endl;
            break;
        }
    }
}

/**
 * Function: main
 * --------------
 * Provides the entry point of the entire program.
 */
int main() {
    LifeDisplay diagram;
    diagram.setTitle("Game of Life");
    welcome();

    cout << "You can start your colony with random cells or read from a prepared file.";
    while (true) {
        // initialize
        string choice = getLine("Enter name of colony file (or RETURN to seed randomly): ");
        Grid<int> currentAge;
        int row, col;
        if (choice == "") {
            random(currentAge, row, col);
            diagram.setTitle("Random Colony");
        } else if (fileExists("D:/Users/Zhu Jun/Documents/Stanford CS106/CS106/Assignment/assign-1-game-of-life/res/files/" + choice)) {
            tailor(choice, currentAge, row, col);
            diagram.setTitle(choice);
        } else {
            cout << "Unable to open the file named " << choice << ".  Please select another file." << endl;
            continue;
        }
        diagram.setDimensions(row, col);
        Grid<int> next(row, col);
        for(int r = 0; r < row; r++) {
            for(int c = 0; c < col; c++) {
                diagram.drawCellAt(r, c, currentAge[r][c]);
            }
        }
        diagram.repaint();
        int delay = getSleepTime();
        while (true) {
            if (delay == -1) {
                getLine();
            } else {
                pause(delay);
            }
            nextGen(currentAge, next, diagram);
        }
    }
    return 0;
}

void tailor(string choice, Grid<int>& currentAge, int& row, int& col) {
    ifstream input;
    string address = "D:/Users/Zhu Jun/Documents/Stanford CS106/CS106/Assignment/assign-1-game-of-life/res/files/" + choice;
    input.open(address.c_str());
    string rowstr, colstr;
    while (getline(input, rowstr)) {
        if (rowstr.length() > 0 && rowstr[0] != '#') {
            break;
        }
    }
    getline(input, colstr);
    row = stringToInteger(rowstr);
    col = stringToInteger(colstr);
    currentAge.resize(row, col);
    string line;
    int r = 0;
    while (getline(input, line)) {
        for (int c = 0; c < col; c++) {
            if (line[c] == 'X') {
                currentAge[r][c] = 1;
            }
            else if (line[c] == '-') {
                currentAge[r][c] = 0;
            }
        }
        r++;
    }
}


void random(Grid<int>& currentAge, int& row, int& col) {
    row = randomInteger(RANMIN, RANMAX);
    col = randomInteger(RANMIN, RANMAX);
    currentAge.resize(row, col);
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            currentAge[r][c] = randomInteger(0, 1);
        }
    }
}

void nextGen(Grid<int>& currentAge, Grid<int>& next, LifeDisplay& diagram) {
    for (int r = 0; r < currentAge.numRows(); r++) {
        for (int c = 0; c < currentAge.numCols(); c++) {
            int neighborCount = 0;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    int nr = r + i;
                    int nc = c + j;
                    if (currentAge.inBounds(nr, nc) && (i || j)
                        && currentAge[nr][nc] > 0) {
                        neighborCount++;
                    }
                }
            }
            switch (neighborCount) {
            case 0:
            case 1:
                next[r][c] = 0;
                break;
            case 2:
                next[r][c] = currentAge[r][c] ? currentAge[r][c] + 1 : 0;
                break;
            case 3:
                next[r][c] = currentAge[r][c] + 1;
                break;
            default:
                next[r][c] = 0;
                break;
            }
            diagram.drawCellAt(r, c, next[r][c]);
        }
    }
    diagram.repaint();
    if (currentAge != next) {
        currentAge = next;
        next.resize(currentAge.numRows(), currentAge.numCols());
    }
}
