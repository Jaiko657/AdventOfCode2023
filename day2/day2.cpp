#include <fstream>
#include <iostream>
#include <string>

#define MAX_RED 12
#define MAX_GREEN 13
#define MAX_BLUE 14

enum Color {
    RED,
    GREEN,
    BLUE
};
struct BallCount {
    int count;
    Color color;
};

using namespace std;

int getRoundNumber(char* pch) {
    int roundNumber = 0;
    while (*pch != ':') {
        roundNumber *= 10;
        roundNumber += (int)((*pch) - '0');
        pch++;
    }
    return roundNumber;
}

BallCount getBallCount(char*& pch) {
    BallCount ballCount{};
    while (*pch != ' ') {
        ballCount.count *= 10;
        ballCount.count += (int)((*pch) - '0');
        pch++;
    }
    pch++;
    switch (*pch) {
    case 'r':
        ballCount.color = RED;
        pch += 3;
        break;
    case 'g':
        ballCount.color = GREEN;
        pch += 5;
        break;
    case 'b':
        ballCount.color = BLUE;
        pch += 4;
        break;
    }
    return ballCount;
}

int getRoundPower(std::string line) {
    char* pch = &line[6];
    int currentMaxRed = 0;
    int currentMaxGreen = 0;
    int currentMaxBlue = 0;
    while (*pch != ':') pch++;
    pch++;
    //pointer at to start game now

    while (*pch != '\0') {
        if (*pch == ';')
            pch += 2;
        else if (*pch == ',')
            pch += 2;
        else {
            BallCount bc = getBallCount(pch);
            switch (bc.color) {
            case RED:
                if (bc.count > currentMaxRed) {
                    currentMaxRed = bc.count;
                }
                break;
            case GREEN:
                if (bc.count > currentMaxGreen) {
                    currentMaxGreen = bc.count;
                }
                break;
            case BLUE:
                if (bc.count > currentMaxBlue) {
                    currentMaxBlue = bc.count;
                }
                break;
            }
        }
    }
    return currentMaxRed * currentMaxGreen * currentMaxBlue;
}

int main() {
    std::ifstream file("input.txt"); // Replace with your file name
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        file.close();
        return 1;
    }
    int sum = 0;
    while (std::getline(file, line)) {
        int round = getRoundNumber(&line[5]);
        int roundPower = getRoundPower(line);
        cout << round << ' ' << roundPower << endl;
        sum += roundPower;
    }
    file.close();
    cout << sum << endl;
    return 0;
}