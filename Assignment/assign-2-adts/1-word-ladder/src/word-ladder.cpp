/**
 * File: word-ladder.cpp
 * ---------------------
 * Implements a program to find word ladders connecting pairs of words.
 */

#include <iostream>
#include <string>
using namespace std;

#include "console.h"
#include "lexicon.h"
#include "strlib.h"
#include "simpio.h"
#include "vector.h"
#include "queue.h"

static string getWord(const Lexicon& english, const string& prompt) {
    while (true) {
        string response = trim(toLowerCase(getLine(prompt)));
        if (response.empty() || english.contains(response)) return response;
        cout << "Your response needs to be an English word, so please try again." << endl;
    }
}

static void generateLadder(const Lexicon& english, const string& start, const string& end) {
    cout << "Here's where you'll search for a word ladder connecting \"" << start << "\" to \"" << end << "\"." << endl;
    int l = start.length();
    Vector<string> ladder {start};
    Queue<Vector<string> > q {ladder};
    Set<string> visited {start};
    while (!q.isEmpty()) {
        Vector<string> wordladder = q.dequeue();
        string word = wordladder[wordladder.size()-1];
        if (word == end) {
            cout << "Found ladder:";
            for (string s : wordladder) {
                cout << " " << s;
            }
            cout << endl << endl;
            return;
        }
        for (int i = 0; i < l; i++) {
            for (char c = 'a'; c <= 'z'; c++) {
                string tempword = word;
                tempword[i] = c;
                if (english.contains(tempword) && !visited.contains(tempword)) {
                    Vector<string> newladder = wordladder;
                    newladder.add(tempword);
                    q.enqueue(newladder);
                    visited.add(tempword);
                }
            }
        }
    }

    // 该单词没有邻近的单词，queue为空
    cout << "No word ladder found." << endl;
}

static const string kEnglishLanguageDatafile = "res/dictionary.txt";
static void playWordLadder() {
    Lexicon english(kEnglishLanguageDatafile);
    while (true) {
        string start = getWord(english, "Please enter the source word [return to quit]: ");
        if (start.empty()) break;
        string end = getWord(english, "Please enter the destination word [return to quit]: ");
        if (end.empty()) break;
        if (start.length() != end.length()) {
            cout << "The two endpoints must contain the same number of characters, or else no word ladder can exist." << endl;
        } else {
            generateLadder(english, start, end);
        }
    }
}

int main() {
    cout << "Welcome to the CS106 word ladder application!" << endl << endl;
    playWordLadder();
    cout << "Thanks for playing!" << endl;
    return 0;
}
