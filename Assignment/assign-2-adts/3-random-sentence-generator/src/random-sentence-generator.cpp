/**
 * File: random-sentence-generator.cpp
 * -----------------------------------
 * Presents a short program capable of reading in
 * context-free grammar files and generating arbitrary
 * sentences from them.
 *
 * 改题：如果<start>下有多个句子，要将nonterminal随机转化
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
        input.open(getNormalizedFilename(filename).c_str());
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

void replaceToken(Map<string, Vector<string> >& grammar) {
    while (true) {
        bool hasToken = false;
        for (string& sentence : grammar["<start>"]) {
            if (sentence.find('<') != string::npos) {
                int start = sentence.find('<');
                int end = sentence.find('>');
                string token = sentence.substr(start, end - start + 1);
                if (!grammar.containsKey(token) || grammar[token].isEmpty()) continue;
                sentence = sentence.substr(0, start) + grammar[token][randomInteger(0, grammar[token].size() - 1)]
                           + sentence.substr(end + 1, sentence.length() - end);

                if (sentence.find('<') != string::npos) {
                    hasToken = true;
                }
            }
        }
        if (!hasToken) break;
    }
}

void printSentence(Map<string, Vector<string> >& grammar) {
    for (string sentence : grammar["<start>"]) {
        cout << sentence << endl;
    }
}
