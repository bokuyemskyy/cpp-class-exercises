#include <fstream>
#include <iostream>
#include <string>

std::string stripComments(const std::string &code) {
    std::string result;
    bool inString = false, inChar = false, inLineComment = false, inBlockComment = false;

    for (size_t i = 0; i < code.size(); ++i) {
        char c = code[i];
        char next = (i + 1 < code.size()) ? code[i + 1] : '\0';

        if (inLineComment && c == '\n') {
            inLineComment = false;
            result += c;
        } else if (inBlockComment && c == '*' && next == '/') {
            inBlockComment = false;
            ++i;
        } else if (inLineComment || inBlockComment) {
            continue;
        } else if (!inString && !inChar && c == '/' && next == '/') {
            inLineComment = true;
            ++i;
        } else if (!inString && !inChar && c == '/' && next == '*') {
            inBlockComment = true;
            ++i;
        } else {
            result += c;
            if (c == '"' && !inChar && (i == 0 || code[i - 1] != '\\')) inString = !inString;
            if (c == '\'' && !inString && (i == 0 || code[i - 1] != '\\')) inChar = !inChar;
        }
    }

    return result;
}

int main() {
    std::string filePath;
    std::cout << "Enter path to .cpp or .h file: ";
    std::getline(std::cin, filePath);

    std::ifstream inFile(filePath);
    if (!inFile) {
        std::cerr << "Error opening file\n";
        return 1;
    }

    std::string code((std::istreambuf_iterator<char>(inFile)), {});
    inFile.close();

    std::string stripped = stripComments(code);

    std::ofstream outFile(filePath);
    if (!outFile) {
        std::cerr << "Error writing to file\n";
        return 1;
    }

    outFile << stripped;
    outFile.close();

    std::cout << "Comments stripped successfully\n";
    return 0;
}
