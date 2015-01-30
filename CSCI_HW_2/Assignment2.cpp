#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int array_size = 100;
int doublings = 0;
int uniques = 0;
int words_total = 0;
string filename;
const string commons[] = { "the", "be", "to", "of", "and", "a", "in", "that", "have", "i",
                           "it", "for", "not", "on", "with", "he", "as", "you", "do", "at",
                           "this", "but", "his", "by", "from", "they", "we", "say", "her", "she",
                           "or", "an", "will", "my", "one", "all", "would", "there", "their", "what",
                           "so", "up", "out", "if", "about", "who", "get", "which", "go", "me" };

struct word {
    string str;
    int num;
} *words = new word[100];

void print_top(int n) {
    word *tops = new word[n];
    for (int i = 0; i <= n; i++) {
        word cur_top;
        for (int index = 0; index < array_size; index++) {
            if (words[index].str.empty()) {
                break;
            }
            if (i == n) {
                if (words[index].num == tops[i - 1].num) {
                    if (tops[i - 1].str.compare(words[index].str) > 0) {
                        tops[i - 1].str = words[index].str;
                    }
                }
            }
            else if (words[index].num >= cur_top.num) {
                bool added = false;
                for (int j = 0; j < i; j++) {
                    if (tops[j].str.compare(words[index].str) == 0) {
                        added = true;
                        break;
                    }
                }
                if (!added) {
                    cur_top.str = words[index].str;
                    cur_top.num = words[index].num;
                }
            }
        }
        if (i < n) {
            tops[i].str = cur_top.str;
            tops[i].num = cur_top.num;
            cur_top.str = "";
            cur_top.num = 0;
        }
    }
    for (int i = 0; i < n - 1; i++) {
        if (tops[i].num == tops[i + 1].num) {
            if (tops[i].str.compare(tops[i + 1].str) < 0) {
                string s = tops[i + 1].str;
                tops[i + 1].str = tops[i].str;
                tops[i].str = s;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << tops[i].num << " - " << tops[i].str << endl;
    }
}

//double the array words[]
void double_array() {
    doublings++;
    word *temp = new word[array_size * 2];
    for (int i = 0; i < array_size; i++) {
        temp[i].str = words[i].str;
        temp[i].num = words[i].num;
    }
    delete[] words;
    words = new word[array_size * 2];
    for (int i = 0; i < array_size; i++) {
        words[i].str = temp[i].str;
        words[i].num = temp[i].num;
    }
    array_size *= 2;
    delete[] temp;
}

void addWord(string s) {
    words_total++;
    for (int i = 0; i < array_size; i++) {
        if (words[i].str.compare(s) == 0) {
            words[i].num++;
            return;
        }
        else if (words[i].str.empty()) {
            uniques++;
            words[i].str = s;
            words[i].num = 1;
            return;
        }
        else if (i == array_size - 1) {
            double_array();
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

int main(int argc, char *argv[]) {//
    ifstream infile(argv[1]);
    filename = string(argv[1]);
	string line;
	while (getline(infile, line)) {
        if (line.empty()) {
            continue;
        }
        string word_str = "";
        for (int i = 0; i < line.length(); i++) {
            if ((int(line.at(i)) >= 97 && int(line.at(i)) <= 122) || (int(line.at(i)) >= 48 && int(line.at(i)) <= 57) || line.at(i) == 'Â' || line.at(i) == '«') {
                word_str = word_str + line.at(i);
            }
            else if (line.at(i) == 'â') { //statement for the infamous dash character in hungergames_edit.txt
                addWord("--");
            }
            else {
                if (!word_str.empty()) {
                    if (not_common(word_str)) {
                        addWord(word_str);
                    }
                }
                word_str.clear();
            }
        }
        if (!word_str.empty()) {
            if (not_common(word_str)) {
                addWord(word_str);
            }
            word_str.clear();
        }
	}
	//final printout
	print_top(atoi(argv[2]));
	cout << "#" << endl;
    cout << "Array doubled: " << doublings  << endl;
	cout << "#" << endl;
	cout << "Unique non-common words: " << uniques << endl;
	cout << "#" << endl;
    cout << "Total non-common words: " << words_total << endl;

}
