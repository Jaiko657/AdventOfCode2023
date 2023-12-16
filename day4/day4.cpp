#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

struct CardCount {
	int score;
	int cardAmount;
};

int getStartIndex(string* str) {
    for (int i = 6; true; i++) {
        char ch = str->at(i);
        if (ch == ':') return i+2;
    }
}

int getCardValue(string line) {
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
			score += 1;
		}

		i += 3;
	}
	cout << " Matches: " << score << endl;
	return score;
}

int main() {
    std::ifstream file("input.txt"); // Replace with your file name
    std::string line;
    if (!file.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        file.close();
    }

	vector<CardCount>* cards = new vector<CardCount>();
    while (std::getline(file, line)) {
        //loop over each line
		CardCount cc = { getCardValue(line), 1 };
		cards->push_back(cc);
    }
    file.close();

	int cardsProcessed = 0;
	int vectorIndex = 0;
	while(vectorIndex < cards->size())
	{
		CardCount* cc = &cards->at(vectorIndex);
		if (cc->cardAmount == 0) {
			vectorIndex++;
			continue;
		}
		for (int i = 0; i < cc->score; i++) {
			cards->at(vectorIndex + 1 + i).cardAmount++;
		}
		cardsProcessed++;
		cc->cardAmount--;
	}
	cout << "Amount Of Cards: " << cardsProcessed << endl;

    return 0;
}
