#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

void parseInput(vector<vector<char>>* array) {
    std::ifstream file("input.txt"); // Replace with your file name
    std::string line;
    if (!file.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        file.close();
    }
    while (std::getline(file, line)) {
        vector<char> row = vector<char>();
        for (const char& c : line) {
            row.push_back(c);
        }
        array->push_back(row);
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

            if(isSymbol(array->at(x).at(y))) return true;
        }
    }
    return false;
}

int test() {
    vector<vector<char>> array;
    parseInput(&array);
    size_t rowSize = array.size();
    size_t colSize = array.at(0).size();

    cout << checkAdjacent(&array, 1, 8, rowSize, colSize) << endl;
    return 0;
}

int main() {
    vector<vector<char>> array;
    parseInput(&array);
    size_t rowSize = array.size();
    size_t colSize = array.at(0).size();

    int sum = 0;

    int currentNum = 0;
    bool isAdjacent = false;
    for (int row = 0; row < rowSize; row++) {
        for (int col = 0; col < colSize; col++) {
            char cellChar = array.at(row).at(col);
            int cellInt = charToInt(cellChar);
            if (cellInt == -1) {
                if (currentNum != 0) {
                    cout << currentNum << " " << isAdjacent << endl;
                    if(isAdjacent) {
                        sum += currentNum;
                    }
                    currentNum = 0;
                    isAdjacent = false;
                }
            }
            else {
				isAdjacent = isAdjacent || checkAdjacent(&array, row, col, rowSize, colSize);
                currentNum *= 10;
                currentNum += cellInt;
            }
            if (col == colSize - 1) {
                if (currentNum != 0) {
                    cout << currentNum << " " << isAdjacent << endl;
                    if(isAdjacent) {
                        sum += currentNum;
                    }
                    currentNum = 0;
                    isAdjacent = false;
                }
            }
        }
    }
    cout << "Sum: " << sum << endl;
    return 0;
}
