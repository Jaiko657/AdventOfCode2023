#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct cord {
	int x;
	int y;
};

int getDistance(cord c1, cord c2) {
    int xDistance = c1.x - c2.x;
    int yDistance = c1.y - c2.y;
    xDistance = abs(xDistance);
    yDistance = abs(yDistance);
    return xDistance + yDistance;
}

int main() {
    //open file
    std::ifstream file("input.txt");
    std::string line;
    if (!file.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        file.close();
        return 1;
    }
    //parse file into v
    auto v = vector<vector<char>>();
    while (std::getline(file, line)) {
        // Process each line as needed
        auto vLine = vector<char>();
        bool isEmpty = true;
        for (int i = 0; i < line.length(); i++) {
            auto ch = line.at(i);
            if (ch != '.') isEmpty = false;
            vLine.push_back(ch);
        }
        if (isEmpty) {
            //expand empty rows in v
            v.push_back(vLine);
        }
        v.push_back(vLine);
    }
    file.close();
    //expand empty cols in v
    for (int col = 0; col < v.at(0).size(); col++) {
        bool isEmpty = true;
        for (int row = 0; row < v.size(); row++) {
            auto c = v.at(row).at(col);
            if (c != '.') isEmpty = false;
        }
        if (isEmpty) {
            for (int row2 = 0; row2 < v.size(); row2++) {
                auto* row = &v.at(row2);
                row->insert(row->begin() + col, '.');
            }
            col++;
        }
    }
    //get cords in v with '#'
    auto cords = vector<cord>();
    for (int row = 0; row < v.size(); row++) {
        for (int col = 0; col < v.at(0).size(); col++) {
            auto ch = v.at(row).at(col);
            if (ch != '.') {
                cord c = { row, col };
                cords.push_back(c);
            }
        }
    }

    //find and sum distances
    int sum = 0;
    for (int i = 0; i < cords.size(); i++) {
        for (int j = i + 1; j < cords.size(); j++) {
            sum += getDistance(cords.at(i), cords.at(j));
        }
    }
    cout << sum << endl;
    return 0;
}
