#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>



using namespace std;

typedef unsigned long long ull;

struct cord {
	ull x;
	ull y;
};

ull getDistance(set<ull>* emptyCols, set<ull>* emptyRows, cord c1, cord c2) {
    const ull EMPTY_WIDTH = 1000000;

    // Calculate X distance
    ull xDistance = 0;
    ull startX = min(c1.x, c2.x);
    ull endX = max(c1.x, c2.x);
    ull finalX = startX;
    for (ull x = startX; x < endX; x++) {
        if (emptyCols->find(x) != emptyCols->end()) {
            xDistance += EMPTY_WIDTH;
        }
        else {
            xDistance++;
            finalX = x;
        }
    }

    // Calculate Y distance
    ull yDistance = 0;
    ull startY = min(c1.y, c2.y);
    ull endY = max(c1.y, c2.y);
    for (ull y = startY; y < endY; y++) {
        if (emptyRows->find(y) != emptyRows->end()) {
            yDistance += EMPTY_WIDTH;
        }
        else {
            yDistance++;
        }
    }

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
    set<ull> emptyRows;
    //parse file ullo v
    auto v = vector<vector<char>>();
    while (std::getline(file, line)) {
        // Process each line as needed
        auto vLine = vector<char>();
        bool isEmpty = true;
        for (ull i = 0; i < line.length(); i++) {
            auto ch = line.at(i);
            if (ch != '.') isEmpty = false;
            vLine.push_back(ch);
        }
        if (isEmpty) {
            //find empty rows and add to set
            //size should be current row being processed
            emptyRows.insert(v.size());
        }
        v.push_back(vLine);
    }
    file.close();
    //find empty cols and add to set
    set<ull> emptyCols;
    for (ull col = 0; col < v.at(0).size(); col++) {
        bool isEmpty = true;
        for (ull row = 0; row < v.size(); row++) {
            auto c = v.at(row).at(col);
            if (c == '#') isEmpty = false;
        }
        if (isEmpty) {
            emptyCols.insert(col);
        }
    }
    //add galaxy cords to vector
    auto cords = vector<cord>();
    for (ull row = 0; row < v.size(); row++) {
        for (ull col = 0; col < v.at(0).size(); col++) {
            auto ch = v.at(row).at(col);
            if (ch == '#') {
                cord c = { col, row };
                cords.push_back(c);
            }
        }
    }

    //find and sum distances
    ull sum = 0;
    for (ull i = 0; i < cords.size(); i++) {
        for (ull j = i + 1; j < cords.size(); j++) {
            sum += getDistance(&emptyCols, &emptyRows, cords.at(i), cords.at(j));
        }
    }
    cout << sum << endl;
    return 0;
}
