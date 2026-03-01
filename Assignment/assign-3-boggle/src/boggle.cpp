/**
 * File: boggle.cpp
 * ----------------
 * Implements the game of Boggle.
 *
 * 我需要完成的是用户选择configution的实现
 * （一种是shuffle后结合成grid；
 * 另一种是用户的16/25-string设置成grid;然后把grid用给的函数读取到图形方格。
 * 然后先找到所有的可行单词存入集合X
 * （关键算法，同时存储路径？这就显示出grid“邻居”的collection好处），
 * 然后用户输入看是不是在X以及在不在lexicon以及长度来看报错，正确得分，用户的输入存入集合Y；
 * 最后计算机直接输出集合X-Y，正确得分。
 */

#include <cctype>
#include <iostream>
#include <ctype.h>
#include "console.h"
#include "gboggle.h"
#include "simpio.h"
#include "strlib.h"
#include "vector.h"
#include "random.h"
#include "grid.h"
#include "map.h"
#include "set.h"
#include "lexicon.h"
using namespace std;

static const string kStandardCubes[16] = {
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

static const string kBigBoggleCubes[25] = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

static const int kMinLength = 4;
static const double kDelayBetweenHighlights = 100;
static const double kDelayAfterAllHighlights = 500;
Set<string> words;
Set<string> humanGuessed;
Vector<GridLocation> path;
Map<string, Vector<GridLocation> > pathMap;
const Lexicon english("res/dictionary.txt");

void configBoard(Grid<char>& board, int dimension);
void precompute(Grid<char>& board, int dimension, string prefix = "");
void humanTurn();
void computerTurn();

/**
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */
static void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl;
    cout << endl;
}

/**
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */
static void giveInstructions() {
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl;
    cout << endl;
    cout << "Hit return when you're ready...";
    getLine(); // ignore return value
}

/**
 * Function: getPreferredBoardSize
 * -------------------------------
 * Repeatedly prompts the user until he or she responds with one
 * of the two supported Boggle board dimensions.
 */

static int getPreferredBoardSize() {
    cout << "You can choose standard Boggle (4x4 grid) or Big Boggle (5x5 grid)." << endl;
    return getIntegerBetween("Which dimension would you prefer: 4 or 5?", 4, 5);
}

/**
 * Function: playBoggle
 * --------------------
 * Manages all details needed for the user to play one
 * or more games of Boggle.
 */
static void playBoggle() {
    int dimension = getPreferredBoardSize();
    drawBoard(dimension, dimension);
    Grid<char> board(dimension, dimension);
    configBoard(board, dimension);
    precompute(board, dimension);
    humanTurn();
    computerTurn();
    cout << "This is where you'd play the game of Boggle" << endl;
}

/**
 * Function: main
 * --------------
 * Serves as the entry point to the entire program.
 */
int main() {
    GWindow gw(kBoggleWindowWidth, kBoggleWindowHeight);
    initGBoggle(gw);
    welcome();
    if (getYesOrNo("Do you need instructions?")) giveInstructions();
    do {
        playBoggle();
    } while (getYesOrNo("Would you like to play again?"));
    cout << "Thank you for playing!" << endl;
    shutdownGBoggle();
    return 0;
}

void configBoard(Grid<char>& board, int dimension) {
    cout << "I'll give you a chance to set up the board to your specification";
    cout << ", which makes it easier to confirm your boggle program is working." << endl;
    string letters;
    int capacity = dimension * dimension;
    if (getYesOrNo("Do you want to force the board configuration?")) {
        // manual
        cout << "Enter a " << capacity << "-character string to identify which letters you want on the cubes." << endl;
        cout << "The first " << dimension << " characters form the top row, ";
        cout << "the next " << dimension << " characters form the second row, and so forth." << endl;
        letters = getLine("Enter a string: ");
        while (letters.length() != capacity) {
            cout << "Enter a string that's precisely " << capacity <<" characters long." << endl;
            letters = getLine("Try again: ");
        }
    } else {
        // random
        // const string *cubes = (dimension == 4 ? kStandardCubes : kBigBoggleCubes);
        // for (int i = 0; i < capacity; i++) {
        //     string face = cubes[i];
        //     char ch = face[randomInteger(0, 5)];
        //     letters += ch;
        // }
        Vector<string> dice;
        for (int i = 0; i < capacity; i++) {
            if (dimension == 4) {
                dice.add(kStandardCubes[i]);
            } else if (dimension == 5) {
                dice.add(kBigBoggleCubes[i]);
            }
        }

        // Fisher-Yates shuffle
        for (int i = 0; i < capacity; i++) {
            int r = randomInteger(i, capacity - 1);
            swap(dice[i], dice[r]); // 其实就是在i到末尾随机选一个数到i（用一个另一个向量思考更好理解）
        }

        letters = "";
        for (int i = 0; i < capacity; i++) {
            string faces = dice[i];
            char ch = faces[randomInteger(0, 5)];
            letters += ch;
        }
    }
    letters = toUpperCase(letters);
    board.resize(dimension, dimension);
    for (int i = 0; i < capacity; i++) {

        int r = i / dimension;
        int c = i % dimension;
        char ch = letters[i];
        board[r][c] = ch;
        labelCube(r, c, ch);
    }
}

// 目的：计算一个已知合格的前缀再加一个字母是否仍然是前缀
// 首先，要遍历board每个字母作为开头，即prefix+ch，判断是否containsPrefix
// 那么开启递归：在该字母的neighbor遍历ch再precompute
// 一旦是合法单词就加入集合 words
void precomputeHelper(Grid<char>& board, int dimension, string prefix, int r, int c, Grid<bool>& used) {
    used[r][c] = true; // choose
    path.add({r, c}); // choose
    for (int i = -1; i <= 1; i++){
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int nr = r + i;
            int nc = c + j;

            if (board.inBounds(nr, nc) && !used[nr][nc]) {
                prefix.push_back(board[nr][nc]); // choose
                if (english.contains(prefix)
                    && prefix.length() >= 4
                    && !words.contains(prefix)) {
                    words.add(prefix);
                    path.add({nr, nc});
                    pathMap[prefix] = path;
                    return;
                } else if (english.containsPrefix(prefix)) {
                    precomputeHelper(board, dimension, prefix, nr, nc, used);
                } // else if 最终没有形成单词
                prefix.pop_back(); // unchoose
                path.remove(path.size() - 1); // unchoose
                used[r][c] = false; // unchoose
            }
        }
    }
}

void precompute(Grid<char>& board, int dimension, string prefix) { // C++ 规定：默认参数只能在某一次“声明”里给出一次（通常放在 .h 或最早的声明里），后面再声明/定义时不能重复写。
    for (int r = 0; r < dimension; r++) {
        for (int c = 0; c < dimension; c++) {
            Grid<bool> used(dimension, dimension, false);
            prefix.push_back(board[r][c]);                 // 选起点字母
            precomputeHelper(board, dimension, prefix, r, c, used);
            prefix.pop_back();
        }
    }
}

void humanOneTurn(string answer) {
    if (!english.contains(answer)) {
        cout << "Sorry, that isn't even a word." << endl;
        return;
    } else if (answer.length() < 4) {
        cout << "Sorry, that isn't long enough to even be considered." << endl;
        return;
    } else if (!words.contains(answer)) {
        cout << "That word can't be constructed with this board." << endl;
        return;
    } else if (humanGuessed.contains(answer)) {
        cout << "You've already guessed that word." << endl;
        return;
    }

    humanGuessed.add(answer);
    cout << "Correct!" << endl;
    for (GridLocation cube : pathMap[answer]) {
        highlightCube(cube.row, cube.col, true);
        pause(500);
    }
    recordWordForPlayer(answer, HUMAN);
    for (GridLocation cube : pathMap[answer]) {
        highlightCube(cube.row, cube.col, false);
    }
}

void humanTurn() {
    while (true) {
        string answer = toUpperCase(getLine("Enter a word: "));
        if (answer == "") {
            cout << "You've completed your turn" << endl;
            return;
        }
        humanOneTurn(answer);
    }
}

void computerTurn() {
    Set<string> computerGuessed = words - humanGuessed;
    for (string answer : computerGuessed) {
        recordWordForPlayer(answer, COMPUTER);
    }
}
