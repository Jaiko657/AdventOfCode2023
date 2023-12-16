#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Race {
    int time;
    int distance;
};

vector<Race>* parseInput() {
    auto* races = new std::vector<Race>();
    std::ifstream file("input.txt");
    std::string line;
    std::vector<int> times, distances;

    // Read Time Line
    if (getline(file, line)) {
        std::istringstream iss(line.substr(line.find(":") + 1));
        int time;
        while (iss >> time) {
            times.push_back(time);
        }
    }

    // Read Distance Line
    if (getline(file, line)) {
        std::istringstream iss(line.substr(line.find(":") + 1));
        int distance;
        while (iss >> distance) {
            distances.push_back(distance);
        }
    }

    // Close the file
    file.close();

    // Store the values in the vector
    for (size_t i = 0; i < times.size(); ++i) {
        races->push_back({ times[i], distances[i] });
    }

    return races;
}

int main() {
    vector<Race>* races = parseInput();
    
    int final = 1;
    for (int i = 0; i < races->size(); i++) {
        Race* race = &races->at(i);
        int raceWinCount = 0;

        const int maxTime = race->time;
        for (int time = 1; time < maxTime; time++) {
            int distanceTravelled = (time * maxTime) - (time * time);
            if (distanceTravelled > race->distance) {
                raceWinCount++;
            }
        }
        final *= raceWinCount;
    }
    cout << final << endl;
    return 0;
}
