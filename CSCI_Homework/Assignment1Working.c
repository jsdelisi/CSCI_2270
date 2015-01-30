#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int steps = 0;
int sold = 0;
int remaining = 0;

struct item {
	string type;
	int price;
	bool forSale;
} posts[100];

int checkForMatch(int loc) {
    for (int i = 0; i < loc; i++) {
        if (posts[i].forSale == posts[loc].forSale) {
            if (posts[i].type.compare(posts[loc].type) == 0) {
                if (posts[i].forSale && posts[i].price >= posts[loc].price) {
                    return i;
                }
                else if (posts[loc].forSale && posts[i].price <= posts[loc].price) {
                    return i;
                }
            }
        }
    }
    return -1;
}

void clear_element(int loc, int cur_size) {
    posts[loc].type = "";
    posts[loc].price = 0;
    posts[loc].forSale = false;
    for (int i = loc; i < cur_size; i++) {
        posts[i].type = posts[i + 1].type;
        posts[i].price = posts[i + 1].price;
        posts[i].forSale = posts[i + 1].forSale;
    }
}

void printItem(int i) {
    if (posts[i].forSale) {
        cout << posts[i].type << " for sale " << posts[i].price << endl;
    }
    else {
        cout << posts[i].type << " wanted " << posts[i].price << endl;
    }
}

int main(int argc, char *argv[]){
	ifstream infile("messageBoard.txt");
	string line;
	int i = 0;
	while (getline(infile, line)) {
        steps++;
		istringstream iss(line);
		posts[i].type = line.substr(0, line.find_first_of(',', 0));
		posts[i].forSale = (line.find("for sale", 0) < line.length());
		int temp = line.find_last_of(' ', line.length() - 1) + 1;
		string str = line.substr(temp, line.length() - temp);
		char *str_array = new char[str.length()];
		for (int i = 0; i < str.length(); i++) {
            str_array[i] = str.at(i);
		}
        posts[i].price = atoi(str_array);
        delete[] str_array;
        printItem(i);
        int match = checkForMatch(i);
        if (match != -1) {
            sold++;
            if (posts[match].forSale) {
                cout << posts[match].type << " " << posts[match].price << endl;
            }
            else {
                cout << posts[i].type << " " << posts[i].price << endl;
            }
            clear_element(i, i);
            clear_element(match, i);
            i -= 2;
        }
		i++;
	}
	cout << "#" <<endl;
	for (int index = 0; index < 100; index++) {
        if (posts[index].type.empty()) {
            break;
        }
        if (posts[index].forSale) {
            cout << posts[index].type<< ", " << "for sale" << ", " << posts[index].price << endl;
        }
        else {
            cout << posts[index].type<< ", " << "wanted" << ", " << posts[index].price << endl;
        }
        remaining++;
	}
	cout << "#" << endl;
	cout<< "operations:" << steps << endl;
	return 0;
}
