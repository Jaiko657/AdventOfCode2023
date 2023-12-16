#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef unsigned long long int ULLInt;

struct Race {
    ULLInt time;
    ULLInt distance;
};

vector<Race>* parseInput() {
    auto* races = new std::vector<Race>();
    std::ifstream file("input.txt");
    std::string line;

    // Read Time Line
    if (getline(file, line)) {
        ULLInt time = 0;
        std::istringstream iss(line.substr(line.find(":") + 1));
        char digit;
        while (iss >> digit) {
            if (isdigit(digit)) {
                time = time * 10 + (digit - '0');
            }
        }

        // Read Distance Line
        if (getline(file, line)) {
            ULLInt distance = 0;
            std::istringstream iss(line.substr(line.find(":") + 1));
            while (iss >> digit) {
                if (isdigit(digit)) {
                    distance = distance * 10 + (digit - '0');
                }
            }

            // Store in vector
            races->push_back({ time, distance });
        }
    }

    // Close the file
    file.close();

    return races;
}

int main() {
    vector<Race>* races = parseInput();
    
    int final = 1;
    for (int i = 0; i < races->size(); i++) {
        Race* race = &races->at(i);
        ULLInt raceWinCount = 0;

        const ULLInt maxTime = race->time;
        for (ULLInt time = 1; time < maxTime; time++) {
            ULLInt distanceTravelled = (time * maxTime) - (time * time);
            if (distanceTravelled > race->distance) {
                raceWinCount++;
            }
        }
        final *= raceWinCount;
    }
    cout << final << endl;
    return 0;
}
