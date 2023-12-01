#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int getNumber(char *ch) {
    if (isdigit(*ch)) return (int)((*ch) - '0');
    
    if (strncmp(ch, "one", 3) == 0)
        return 1;
    else if (strncmp(ch, "two", 3) == 0)
        return 2;
    else if (strncmp(ch, "three", 5) == 0)
        return 3;
    else if (strncmp(ch, "four", 4) == 0)
        return 4;
    else if (strncmp(ch, "five", 4) == 0)
        return 5;
    else if (strncmp(ch, "six", 3) == 0)
        return 6;
    else if (strncmp(ch, "seven", 5) == 0)
        return 7;
    else if (strncmp(ch, "eight", 5) == 0)
        return 8;
    else if (strncmp(ch, "nine", 4) == 0)
        return 9;
    return -1;
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
        // Process each line as needed
        int currentNumber = 0;
        for (int i = 0; i < line.size(); i++) {
            int num = getNumber(&line[i]);
            if (num == -1) continue;
            currentNumber = num;
            break;
        }
        currentNumber *= 10;
        for (int i = line.size()-1; i >= 0; i--) {
            int num = getNumber(&line[i]);
            if (num == -1) continue;
            currentNumber += num;
            break;
        }
        sum += currentNumber;
    }
    file.close();
    cout << sum << endl;
	return 0;
}