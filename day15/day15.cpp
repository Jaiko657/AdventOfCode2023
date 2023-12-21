#include <string>
#include <fstream>
#include <iostream>

using namespace std;

int main() {
    std::ifstream file("input.txt"); // Replace with your file name
    std::string line;
    if (!file.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        file.close();
        return 1;
    }
    getline(file, line);

    uint64_t sum = 0;
    int currentValue = 0;
    char* ch = &line[0];
    while (true) {
        if (*ch == ',' || *ch == '\0') {
            cout << ": " << currentValue << endl;
            sum += currentValue;
            currentValue = 0;
            if (*ch == '\0') {
                break;
            }
            ch++;
            continue;
        }
        cout << *ch;
        int asciiValue = static_cast<int>(*ch);
        currentValue += asciiValue;
        currentValue *= 17;
        currentValue %= 256;
        ch++;
    }
    cout << endl << sum << endl;
    return 0;
}