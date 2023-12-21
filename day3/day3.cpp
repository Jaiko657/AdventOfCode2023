#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

struct cord {
    int x;
    int y;
};

struct numCord {
    int num;
    cord crd;
};

void parseInput(vector<vector<char>>* array, vector<cord>* cords) {
    std::ifstream file("input.txt"); // Replace with your file name
    std::string line;
    if (!file.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        file.close();
    }
    int y = 0;
    while (std::getline(file, line)) {
        vector<char> row = vector<char>();
        int x = 0;
        for (const char& ch : line) {
            row.push_back(ch);
            if (ch == '*') {
                cord c = { x, y };
                cords->push_back(c);
            }
            x++;
        }
        array->push_back(row);
        y++;
    }
    file.close();
}

inline int charToInt(const char& c) {
    int num = (int)(c - '0');
    if (num < 0 || num > 9) return -1;
    return num;
}

inline bool isSymbol(const char& c) {
	return c != '.' && !isdigit(c);
}

bool checkAdjacent(vector<vector<char>>* array, int row, int col, size_t rowSize, size_t colSize) {
    //cout << "Checking: " << array->at(row).at(col) << endl;
    for (int x = row - 1; x <= row + 1; x++) {
        for (int y = col - 1; y <= col + 1; y++) {
            //skip middle
            if (x == row && y == col) continue;
            //skip negative vector access
            if (x < 0 || y < 0) continue;
            //skip out of bounds vector access
            if (x > rowSize - 1 || y > colSize - 1) continue;

            if(array->at(x).at(y) == '*') return true;
        }
    }
    return false;
}

bool areAdjacent(const cord& a, const cord& b) {
    int xDiff = std::abs(a.x - b.x);
    int yDiff = std::abs(a.y - b.y);

    // Adjacent if either x or y difference is 1 and the other is 0 or 1
    return (xDiff <= 1) && (yDiff <= 1) && !(xDiff == 0 && yDiff == 0);
}

int main() {
    vector<vector<char>> array;
    vector<cord> cogCords;
    vector<numCord> numCords;
    parseInput(&array, &cogCords);
    size_t rowSize = array.size();
    size_t colSize = array.at(0).size();

    int currentNum = 0;
    bool isAdjacent = false;
    cord c = { -1,-1 };
    for (int row = 0; row < rowSize; row++) {
        for (int col = 0; col < colSize; col++) {
            char cellChar = array.at(row).at(col);
            int cellInt = charToInt(cellChar);
            if (cellInt == -1) {
                if (currentNum != 0) {
                    //cout << currentNum << " " << isAdjacent << endl;
                    if(isAdjacent) {
                        numCord nC = { currentNum, c };
                        numCords.push_back(nC);
                    }
                    currentNum = 0;
                    isAdjacent = false;
                }
            }
            else {
                if (!isAdjacent) {
				    isAdjacent =  checkAdjacent(&array, row, col, rowSize, colSize);
					if (isAdjacent) {
						c = {col, row};
					}
                }
                currentNum *= 10;
                currentNum += cellInt;
            }
            if (col == colSize - 1) {
                if (currentNum != 0) {
                    //cout << currentNum << " " << isAdjacent << endl;
                    if(isAdjacent) {
                        numCord nC = { currentNum, c };
                        numCords.push_back(nC);
                    }
                    currentNum = 0;
                    isAdjacent = false;
                }
            }
        }
    }

    int total = 0;
    for (cord c : cogCords) {
        cout << "Calculating Cord: " << c.x << ", " << c.y << endl;
        int amount = 0;
        int sum = 1;
        for (numCord nC : numCords) {
            if(amount > 2) break;
            if (areAdjacent(c,nC.crd)) {
                amount++;
                cout << nC.num << endl;
                sum *= nC.num;
            }
        }
        if (amount == 2) {
            cout << "Sum: " << sum << endl;
            total += sum;
        }
    }
    cout << total << endl;
    return 0;
}
