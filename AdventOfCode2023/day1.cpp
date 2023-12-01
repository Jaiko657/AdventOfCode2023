#include <fstream>
#include <iostream>
#include <string>

using namespace std;

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
            if (!isdigit(line[i])) continue;
            currentNumber = line[i] - '0';
            break;
        }
        currentNumber *= 10;
        for (int i = line.size()-1; i >= 0; i--) {
            if (!isdigit(line[i])) continue;
            currentNumber += line[i] - '0';
            break;
        }
        sum += currentNumber;
    }
    file.close();
    cout << sum << endl;
	return 0;
}