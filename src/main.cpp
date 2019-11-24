#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include <set>
#include <iomanip> // setw


#include "dictionary.h"

using namespace std;

void lower(string &s);

string stripPunct(const string &s);

void checkSpelling(ifstream &in, Dictionary &dict);

void generateTransposing(set<string> &totest, string origin);

void generateRemoval(set<string> &totest, string origin);

void generateReplacement(set<string> &totest, string origin);

void generateInserting(set<string> &totest, string origin);

void removeNonWords(set<string> &totest, Dictionary &dict);

void printMistake(string &word, set<string> &answer, int line);

// program arguments to run, example: main.exe ../../res/wordlist.txt ../../res/test.txt
int main(int argc, char *argv[]) {


    // Output usage message if improper command line args were given.
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " wordlist_filename input_file\n";
        return EXIT_FAILURE;
    }

    ifstream inf(argv[2]);
    if (!inf) {
        cerr << "Could not open " << argv[2] << "\n";
        return EXIT_FAILURE;
    }

    // Read dictionary, but let user know what we are working on.
    cout << "Loading dictionary, this may take awhile...\n";

    Dictionary d(argv[1]);

    checkSpelling(inf, d);

    inf.close();

    return EXIT_SUCCESS;
}

void checkSpelling(ifstream &in, Dictionary &dict) {

    int line_number = 0;

    while (in) {
        line_number++;

        string line;
        getline(in, line);

        stringstream ss(stringstream::in | stringstream::out);
        ss << line;

        string word;
        while (ss >> word) {
            set<string> totest;

            word = stripPunct(word);
            lower(word);

            if (dict.search(word))
                continue;

            generateTransposing(totest, word);
            generateInserting(totest, word);
            generateRemoval(totest, word);
            generateReplacement(totest, word);

            removeNonWords(totest, dict);

            printMistake(word, totest, line_number);
        }
    }
}

void generateTransposing(set<string> &totest, string origin) {

    for (int i = 0; i < origin.size() - 1; i++) {
        int j = i + 1;
        string newWord = origin;
        newWord[i] = origin[j];
        newWord[j] = origin[i];
        totest.insert(newWord);
    }
}

void generateRemoval(set<string> &totest, string origin) {

    for (int i = 0; i < origin.size(); i++) {
        string newWord = origin;
        newWord.erase(i, 1);
        totest.insert(newWord);
    }
}


void generateReplacement(set<string> &totest, string origin) {

    for (int i = 0; i < origin.size(); i++)
        for (int j = 'a'; j <= 'z'; j++) {
            string newWord = origin;
            newWord[i] = (char) j;
            totest.insert(newWord);
        }
}

void generateInserting(set<string> &totest, string origin) {

    for (int i = 0; i < origin.size(); i++)
        for (int j = 'a'; j <= 'z'; j++) {
            string newWord = origin;
            string ins = "1";
            ins[0] = (char) j;
            newWord.insert(i, ins);
            totest.insert(newWord);
        }
}

void removeNonWords(set<string> &totest, Dictionary &dict) {

    for (auto i = totest.begin(); i != totest.end();) {
        if (!dict.search(*i)) {
            totest.erase(i++);
            continue;
        }
        i++;
    }

}

void printMistake(string &word, set<string> &answer, int line) {

    cout << "mistake in word " << word << "  Line number: " << line << endl;
    cout << "Possible corrections: " << endl;

    for (auto i = answer.begin(); i != answer.end(); i++) {
        cout << *i << endl;
    }

    cout << "\n";
}

void lower(string &s) {

    // Ensures that a word is lowercase
    for (int i = 0; i < s.length(); i++) {
        s[i] = tolower(s[i]);
    }
}

string stripPunct(const string &s) {

    // Remove any single trailing
    // punctuation character from a word.
    if (ispunct(s[s.length() - 1])) {
        return s.substr(0, s.length() - 1);
    } else {
        return s;
    }
}
