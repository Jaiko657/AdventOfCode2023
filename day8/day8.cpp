#include <string>
#include <fstream>
#include <iostream>
using namespace std;

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
    string currentItem = "AAA";

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

    bool makeTurn(char turn) {
        TreeNode* currentNode = data[stringToInt(currentItem)];
        if (turn == 'L') {
            currentItem = currentNode->left;
        }
        else {
            currentItem = currentNode->right;
        }
        if (currentItem == "ZZZ") {
            return true;
        }
        return false;
    }
};

int main() {
    Tree tree;
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
    }

    int i = 0;
    int amountOfMoves = 0;
    bool finished = false;
    while (true) {
        finished = tree.makeTurn(instructions[i]);
        
        amountOfMoves++;
        i++;
        if (i >= instructions.size()) {
            i = 0;
        }
        if (finished) break;
    }
    cout << amountOfMoves << endl;
    return 0;
}
