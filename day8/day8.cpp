#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

typedef unsigned long long uul;

int stringToInt(const string& str) {
    if (str.length() != 3) {
        std::cerr << "String must be exactly 3 characters long." << std::endl;
        return -1; // or handle error as appropriate
    }
    int result = 0;
    for (int i = 0; i < 3; ++i) {
        result *= 256; // Assuming 8 bits per char (standard in most environments)
        result += str[i] - 'A';
    }
    return result;
}

class TreeNode {
public:
    string item;
    string left;
    string right;

    TreeNode(string _item, string _left, string _right) {
        item = _item;
        left = _left;
        right = _right;
    }
};

class Tree {
public:
    //stringToInt("ZZZ") = 1644825
    const int size = 1644825+1;
    TreeNode** data;

    Tree() {
        data = new TreeNode*[size];

        for (int i = 0; i < size; ++i) {
            data[i] = nullptr;
        }
    }
    ~Tree() {
        for (int i = 0; i < size; ++i) {
            delete data[i];
        }
        delete[] data;
    }
    void addTreeNode(string str) {
        auto item = str.substr(0, 3);
        auto left = str.substr(7, 3);
        auto right = str.substr(12, 3);
        TreeNode* node = new TreeNode(item, left, right);
        data[stringToInt(item)] = node;
    }

    bool makeTurn(char turn, string* currentItem) {
        TreeNode* currentNode = data[stringToInt(*currentItem)];
        if (turn == 'L') {
            *currentItem = currentNode->left;
        }
        else {
            *currentItem = currentNode->right;
        }
        if ((*currentItem)[2] == 'Z') {
            return true;
        }
        return false;
    }
};

uul gcd(uul a, uul b) {
    while (b != 0) {
        uul t = b;
        b = a % b;
        a = t;
    }
    return a;
}
uul lcm(uul a, uul b) {
    return a / gcd(a, b) * b; // Multiplying first to avoid potential underflow
}
uul lcmOfVector(const std::vector<int>& nums) {
    uul result = 1;
    for (int num : nums) {
        result = lcm(result, num);
    }
    return result;
}

int main() {
    Tree tree;
    vector<string> currentItems;
    ifstream file("input.txt");
    string line;
    if (!file.is_open()) {
        cerr << "Unable to open file" << endl;
        file.close();
        return 1;
    }

    string instructions;
    getline(file, instructions);
    getline(file, line); //skip empty line

    while (getline(file, line)) {
        tree.addTreeNode(line);
        auto str = line.substr(0, 3);
        if (str[2] == 'A') {
            currentItems.push_back(str);
        }
    }
    file.close();

    vector<int> moveCounts;
    //loop over all the ghost items with 'A' at end
    for (int i = 0; i < currentItems.size(); i++) {
		int instructionIndex = 0;
		int amountOfMoves = 0;
		//loop over instructions
		while (true) {
																		  //is modified
			bool finished = tree.makeTurn(instructions[instructionIndex], &currentItems[i]);
			//move to next instruction
			instructionIndex++;
			if (instructionIndex >= instructions.size()) {
				instructionIndex = 0;
			}
			
			amountOfMoves++;
			if (finished) break;
		}
        moveCounts.push_back(amountOfMoves);
    }
    std::cout << lcmOfVector(moveCounts) << endl;
    return 0;
}
