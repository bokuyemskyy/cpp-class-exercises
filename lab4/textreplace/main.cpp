#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
    std::cout << "Welcome to TextReplacer.\n";

    bool running = true;
    while (running) {
        std::vector<std::string> filenames;

        bool fetching = true;
        while (fetching) {
            std::cout << "Hint: write 'stop' to stop fetching files and 'exit' to exit\n";
            std::cout
                << "I have " << filenames.size()
                << " files to work on.\nWrite the absolute path to a file you want to modify:\n";
            std::string buf;
            std::cin >> buf;
            if (buf == "stop") {
                fetching = false;
                continue;
            }
            if (buf == "exit") {
                fetching = false;
                running = false;
                continue;
            }
        }

        if (!running) continue;
        std::string toReplace, replaceWith;
        std::cout << "What to search for: ";
        std::cin >> toReplace;
        std::cout << "What to replace it with: ";
        std::cin >> replaceWith;

        for (const std::string& filename : filenames) {
            std::ifstream inFile(filename);
            if (!inFile) {
                std::cerr << "Failed to open file for reading: " << filename << "\n";
                continue;
            }

            std::stringstream buffer;
            buffer << inFile.rdbuf();
            std::string content = buffer.str();
            inFile.close();

            size_t pos = 0;
            while ((pos = content.find(toReplace, pos)) != std::string::npos) {
                content.replace(pos, toReplace.length(), replaceWith);
                pos += replaceWith.length();
            }

            std::ofstream outFile(filename);
            if (!outFile) {
                std::cerr << "Failed to open file for writing: " << filename << "\n";
                continue;
            }

            outFile << content;
            outFile.close();
        }
    }
}