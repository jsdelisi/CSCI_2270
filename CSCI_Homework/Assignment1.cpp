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

//function returns the index of posts in that matches with posts[loc], or returns a -1 if theres no match
int checkForMatch(int loc) {
    for (int i = 0; i < loc; i++) {
        steps++;
        if (posts[i].forSale != posts[loc].forSale) { //compares forSales
            if (posts[i].type.compare(posts[loc].type) == 0) { //looks for matching types
                if (posts[i].forSale && posts[i].price <= posts[loc].price) { // checks for matching prices (2 cases)
                    return i;
                }
                else if (posts[loc].forSale && posts[i].price >= posts[loc].price) {
                    return i;
                }
            }
        }
    }
    return -1;
}

//removes an element from posts and shifts down elements
void clear_element(int loc, int cur_size) {
    posts[loc].type = ""; //clears the field of the selected element
    posts[loc].price = 0;
    posts[loc].forSale = false;
    for (int i = loc; i < cur_size; i++) { //shift all subsequent elements down
        steps++;
        posts[i].type = posts[i + 1].type;
        posts[i].price = posts[i + 1].price;
        posts[i].forSale = posts[i + 1].forSale;
    }
}

int main(int argc, char *argv[]){
	ifstream infile(argv[1]); //passed file name is in argv[1]
	string line;
	int i = 0;
	while (getline(infile, line)) {
        //reads in a line a makes a struct item with the given info
		istringstream iss(line);
		posts[i].type = line.substr(0, line.find_first_of(',', 0)); //type = substring from index 0 to one before the first comma
		posts[i].forSale = (line.find("for sale", 0) < line.length()); // item is for sale if "for sale" is found in the input line
		int temp = line.find_last_of(' ', line.length() - 1) + 1; //temp = index of the first digit of the price
		string str = line.substr(temp, line.length() - temp); //substring of the price
		char *str_array = new char[str.length()];
		for (int j = 0; j < str.length(); j++) { //creates a char[] of the price
            str_array[j] = str.at(j);
		}
        posts[i].price = atoi(str_array); //converts the char[] to an int
        delete[] str_array;
        int match = checkForMatch(i);
        //if theres a match, will print out item sold
        if (match != -1) {
            steps++;
            if (posts[match].forSale) {
                cout << posts[match].type << " " << posts[match].price << endl;
            }
            else {
                cout << posts[i].type << " " << posts[i].price << endl;
            }
            clear_element(i, i);
            clear_element(match, i);
            steps++; //clearing the most recent element doesn't count
            i -= 2; //2 elements removed so there is a shift down of 2
        }
		i++;
	}
	cout << "#" <<endl;
	//prints remaining posts
	for (int index = 0; index < 100; index++) {
        steps++;
        if (posts[index].type.empty()) { //if an empty posts is found, will stop printing
            steps--; //removes a step because the most recent addition is an empty post
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
