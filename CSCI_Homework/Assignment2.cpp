#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int array_size = 100;
string commons[] = { "the", "you", "one", "be", "do", "all", "two", "at", "would", "of",
                     "this", "there", "and", "but", "their", "a", "his", "what", "in", "by",
                     "so", "that", "from", "up", "have", "they", "out", "i", "we", "if",
                     "it", "say", "about", "for", "her", "who", "not", "she", "get", "on",
                     "or", "which", "with", "an", "go", "he", "will", "me", "as", "my" };

struct word {
    string str;
    int num;
} *words = new word[100];

void double_array() {
    word *temp = new word[array_size * 2];
    for (int i = 0; i < array_size; i++) {
        temp[i] = words[i];
    }
    words = temp;
    delete[] temp;
}

void addWord(string s) {
    for (int i = 0; i < array_size; i++) {
        if (words[i].str.compare(s) == 0) {
            words[i].num++;
            return;
        }
        else if (words[i].str.empty()) {
            words[i].str = s;
            words[i].num = 1;
            return;
        }
        else if (i == array_size - 1) {
            double_array();
            words[array_size].str = s;
            words[array_size].num = 1;
        }
    }
}

bool not_common(string s) {
    for (int i = 0; i < 50; i++) {
        if (commons[i].compare(s) == 0) {
            return false;
        }
    }
    return true;
}

void prin

int main(int argc, char* argv[]) {
    ifstream infile("test.txt");
	string line;
	int i = 0;
	while (getline(infile, line)) {
        string word_str = "";
        for (int i = 0; i < line.length(); i++) {
            if (line.at(i) == ' ') {
                if (!word_str.empty()) {
                    if (not_common(word_str)) {
                        addWord(word_str);
                    }
                    word_str.clear();
                }
            }
            else {
                word_str = word_str + line.at(i);
            }
        }
        if (!word_str.empty()) {
            if (not_common(word_str)) {
                addWord(word_str);
            }
            word_str.clear();
        }
	}
	print_words();
}
