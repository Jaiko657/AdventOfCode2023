#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

int getStartIndex(string* str) {
    for (int i = 6; true; i++) {
        char ch = str->at(i);
        if (ch == ':') return i+2;
    }
}

int main() {
    std::ifstream file("input.txt"); // Replace with your file name
    std::string line;
    if (!file.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        file.close();
    }

    int scoreSum = 0;
    while (std::getline(file, line)) {
        //loop over each line
        bool* winningNums = new bool[100]();
        int i = getStartIndex(&line);
        int score = 0;
        while(true){
            char ch1 = line.at(i);
            char ch2 = line.at(i+1);
            int currentNum = 0;
            if (ch1 == '|') break;
            
            if (ch1 == ' ') {
                ch1 = '0';
            }
            currentNum += (ch1 - '0')*10;
            currentNum += (ch2 - '0');

            cout << currentNum << " ";
            winningNums[currentNum] = true;

            i += 3;
        }

        //move i to start of next card
        cout << "| ";
        i += 2;
        while(true){
            //stop overflow
            if (i >= line.size()-1) break;
            char ch1 = line.at(i);
            char ch2 = line.at(i+1);
            int currentNum = 0;
            
            if (ch1 == ' ') {
                ch1 = '0';
            }
            currentNum += (ch1 - '0')*10;
            currentNum += (ch2 - '0');

            cout << currentNum << " ";
            if (winningNums[currentNum]) {
                if (score == 0) {
                    score = 1;
                }
                else {
                    score *= 2;
                }
            }

            i += 3;
        }

        scoreSum += score;
		cout << " Score: " << score << endl;
		score = 0;
    }
    cout << "Score Sum: " << scoreSum << endl;
    file.close();

    return 0;
}
