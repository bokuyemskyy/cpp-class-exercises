#include <fstream>
#include <iostream>
#include <limits>
#include <stack>
#include <string>
#include <vector>

class TextEditor {
   private:
    std::string m_filepath;
    std::vector<std::string> m_lines;
    std::string m_copyBuffer;
    std::vector<std::vector<std::string>> m_history;

    void pushState() { m_history.push_back(m_lines); }

    int inputLineNumber() {
        int lineNumber;
        std::cout << "Enter the line number: ";
        std::cin >> lineNumber;
        if (std::cin.fail() || lineNumber < 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return -1;
        }
        return lineNumber;
    }

   public:
    void getFilepath() {
        while (m_filepath.empty()) {
            std::cout << "Enter the filepath: ";
            std::cin >> m_filepath;
        }
    }

    void closeFile() {
        m_filepath.clear();
        m_lines.clear();
        m_history.clear();
    }

    void newFile() {
        closeFile();
        getFilepath();
    }

    void openFile() {
        closeFile();
        getFilepath();
        std::ifstream file(m_filepath);
        std::string line;
        while (std::getline(file, line)) m_lines.push_back(line);
    }

    void saveFile() {
        std::ofstream file(m_filepath);
        for (const auto& line : m_lines) file << line << "\n";
    }

    void editLine() {
        int i = inputLineNumber();
        if (i < 0) return;

        pushState();
        if (i >= m_lines.size()) m_lines.resize(i + 1);
        std::cout << "Current: " << m_lines[i] << "\nNew: ";
        std::cin.ignore();
        std::getline(std::cin, m_lines[i]);
    }

    void cutLine() {
        int i = inputLineNumber();
        if (i < 0 || i >= m_lines.size()) return;

        pushState();
        m_copyBuffer = m_lines[i];
        m_lines.erase(m_lines.begin() + i);
    }

    void copyLine() {
        int i = inputLineNumber();
        if (i < 0 || i >= m_lines.size()) return;

        m_copyBuffer = m_lines[i];
    }

    void pasteLine() {
        int i = inputLineNumber();
        if (i < 0) return;
        pushState();
        if (i > m_lines.size()) m_lines.resize(i);
        m_lines.insert(m_lines.begin() + i, m_copyBuffer);
    }

    void undo() {
        if (!m_history.empty()) {
            m_lines = m_history.back();
            m_history.pop_back();
            std::cout << "Undo done.\n";
        } else {
            std::cout << "Nothing to undo.\n";
        }
    }

    void displayContent() {
        for (int i = 0; i < m_lines.size(); ++i) std::cout << i << ": " << m_lines[i] << "\n";
    }

    void displayMenu() {
        int choice = 0;
        do {
            std::cout << "\n\n\n--------------------------\n";
            std::cout << "|       The Editor       |\n";
            std::cout << "--------------------------\n";
            std::cout << "1. New File\n";
            std::cout << "2. Open File\n";
            std::cout << "3. Save File\n";
            std::cout << "4. Edit Line\n";
            std::cout << "5. Cut Line\n";
            std::cout << "6. Copy Line\n";
            std::cout << "7. Paste Line\n";
            std::cout << "8. Undo\n";
            std::cout << "9. Display Content\n";
            std::cout << "10. Quit\n";
            std::cout << "Choice: ";
            std::cin >> choice;

            switch (choice) {
                case 1:
                    newFile();
                    break;
                case 2:
                    openFile();
                    break;
                case 3:
                    saveFile();
                    break;
                case 4:
                    editLine();
                    break;
                case 5:
                    cutLine();
                    break;
                case 6:
                    copyLine();
                    break;
                case 7:
                    pasteLine();
                    break;
                case 8:
                    undo();
                    break;
                case 9:
                    displayContent();
                    break;
                case 10:
                    return;
            }
        } while (true);
    }
};

int main() {
    TextEditor editor;
    editor.displayMenu();
}