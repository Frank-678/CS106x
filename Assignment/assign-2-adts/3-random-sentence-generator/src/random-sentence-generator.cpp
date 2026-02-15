/**
 * File: random-sentence-generator.cpp
 * -----------------------------------
 * Presents a short program capable of reading in
 * context-free grammar files and generating arbitrary
 * sentences from them.
 */

#include <iostream>
#include <fstream>
#include <random>
#include <string>
using namespace std;

#include "console.h"
#include "map.h"
#include "simpio.h"   // for getLine
#include "strlib.h"   // for toLowerCase, trim
#include "vector.h"

static const string kGrammarsDirectory = "res/grammars/";
static const string kGrammarFileExtension = ".g";
static string getNormalizedFilename(string filename) {
    string normalizedFileName = kGrammarsDirectory + filename;
    if (!endsWith(normalizedFileName, kGrammarFileExtension))
        normalizedFileName += kGrammarFileExtension;
    return normalizedFileName;
}

static bool isValidGrammarFilename(string filename) {
    string normalizedFileName = getNormalizedFilename(filename);
    ifstream infile(normalizedFileName.c_str());
    return !infile.fail();
}

static string getFileName() {
    while (true) {
        string filename = trim(getLine("Name of grammar file? [<return> to quit]: "));
        if (filename.empty() || isValidGrammarFilename(filename)) return filename;
        cout << "Failed to open the grammar file named \"" << filename << "\". Please try again...." << endl;
    }
}

void readGrammar(ifstream& input, Map<string, Vector<string> >& grammar);
void replaceToken(Map<string, Vector<string> >& grammar);
void printSentence(Map<string, Vector<string> >& grammar);

int main() {
    while (true) {
        string filename = getFileName();
        if (filename.empty()) break;
        cout << "Here's where you read in the \"" << filename << "\" grammar "
             << "and generate three random sentences." << endl;

        ifstream input;
        input.open(filename.c_str());
        Map<string, Vector<string> > grammar;
        readGrammar(input, grammar);
        input.close();

        replaceToken(grammar);
        printSentence(grammar);
    }
    
    cout << "Thanks for playing!" << endl;
    return 0;
}

void readGrammar(ifstream& input, Map<string, Vector<string> >& grammar) {
    while (true) {
        string nonTerminal;
        if (!getline(input, nonTerminal)) break;
        if (trim(nonTerminal).empty()) continue;

        string countStr;
        getline(input, countStr);
        int count = stringToInteger(countStr);

        Vector<string> rules;
        for (int i = 0; i < count; i++) {
            string rule;
            getline(input, rule);
            rules.add(rule);
        }

        grammar[nonTerminal] = rules;
    }
}

bool hasToken(Vector<string> start) {
    for (string& sentence : start) {
        if (sentence.find('<') != string::npos) return true;
    }
    return false;
}

void replaceToken(Map<string, Vector<string> >& grammar) {
    while (hasToken(grammar["<start>"])) {
        for (string& sentence : grammar["<start>"]) {
            int start = sentence.find('<');
            int end = sentence.find('>');
            string token = sentence.substr(start, end - start + 1);
            sentence = sentence.substr(0, start) + grammar[token][randomInteger(0, grammar[token].size() - 1)]
                       + sentence.substr(end + 1, sentence.length() - end);
        }
    }
}

void printSentence(Map<string, Vector<string> >& grammar) {
    for (string sentence : grammar["<start>"]) {
        cout << sentence << endl;
    }
}
