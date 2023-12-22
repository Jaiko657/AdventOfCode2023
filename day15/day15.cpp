#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct Lens {
    string label;
    int focalLen;
};
int hashLabel(string label) {
	int currentValue = 0;
	for(const char ch : label) {
		int asciiValue = static_cast<int>(ch);
		currentValue += asciiValue;
		currentValue *= 17;
		currentValue %= 256;
	}
	return currentValue;
}

class Box {
private:
    static const int size = 256;
public:
    vector<Lens>* boxes[size];

    Box() {
        for (int i = 0; i < size; i++) {
            boxes[i] = new vector<Lens>();
        }
    }
    ~Box() {
        for (int i = 0; i < size; i++) {
            delete boxes[i];
        }
    }
    void print() {
		for (int i = 0; i < size; i++) {
            auto box = boxes[i];
            if (box->size() > 0) {
                cout << "Box " << i << ": ";
				for (const Lens lens : *box) {
					cout << "[" << lens.label << " " << lens.focalLen << "] ";
				}
				cout << endl;
            }
		}
    }
    void removeLens(string label) {
        int h = hashLabel(label);
        auto box = boxes[h];
        for(int i = 0; i < box->size(); i++) {
            if (box->at(i).label == label) {
                box->erase(box->begin() + i);
            }
        }
    }
    void addLens(string label, int focalLen) {
        Lens lens = { label, focalLen };
        int h = hashLabel(label);
        auto box = boxes[h];
        for (int i = 0; i < box->size(); i++) {
            if (box->at(i).label == label) {
                box->at(i).focalLen = focalLen;
                return;
            }
        }
        box->push_back(lens);
    }
    void processInstruction(const string& instruction) {
        string label = "";
        char type = ' ';
        int focalLen = -1;
        for (int i = 0; i < instruction.size(); i++) {
            auto ch = instruction[i];
            if (ch != '=' && ch != '-') {
                label += ch;
                continue;
            }
            type = ch;
            if (type == '=') {
                focalLen = (instruction[i + 1] - '0');
            }
            break;
        }
        // - type
        if (focalLen == -1) {
            removeLens(label);
        }
        // = type
        else {
            addLens(label, focalLen);
        }
    }
    int getFocusingPower() {
        int sum = 0;
        for (int boxNumber = 0; boxNumber < size; boxNumber++) {
            for (int slotNumber = 0; slotNumber < boxes[boxNumber]->size(); slotNumber++) {
                int lensPower = (boxNumber + 1) * (slotNumber+1) * boxes[boxNumber]->at(slotNumber).focalLen;
                sum += lensPower;
            }
        }
        return sum;
    }
};
int main() {
    ifstream file("input.txt"); // Replace with your file name
    string line;
    if (!file.is_open()) {
        cerr << "Unable to open file" << endl;
        file.close();
        return 1;
    }
    getline(file, line);
    Box b;

    //line = "rn=1,cm-,qp=3,cm=2,qp-,pc=4,ot=9,ab=5,pc-,pc=6,ot=7";
    string currentSubstring;

    for (char ch : line) {
        if (ch != ',') {
            currentSubstring += ch;
        }
        else {
            if (!currentSubstring.empty()) {
                b.processInstruction(currentSubstring);
                currentSubstring.clear();
            }
        }
    }
    if (!currentSubstring.empty()) {
        b.processInstruction(currentSubstring);
    }

    b.print();
    cout << b.getFocusingPower() << endl;
    return 0;
}