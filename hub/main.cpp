#include <unistd.h>

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

struct ExecEntry {
    std::string name;
    bool cli;
    std::string path;
};

int main() {
    char cwd[4096];
    if (getcwd(cwd, sizeof(cwd)) == nullptr) {
        perror("getcwd() error");
        return 1;
    }
    std::string base_path = cwd;

    std::vector<ExecEntry> executables = {
        {.name = "Lab 1 Tasks altogether", .cli = false, .path = "lab1/all_tasks/main"},
        {.name = "Lab 2 Task 1 (calculator)", .cli = true, .path = "lab2/calculator/main"},
        {.name = "Lab 2 Task 2 (number guessing game)",
         .cli = true,
         .path = "lab2/number_game/main"},
        {.name = "Lab 2 Task 3 (date class)", .cli = false, .path = "lab2/date/main"},
        {.name = "Lab 2 Task 4 (clock and calendar classes)",
         .cli = false,
         .path = "lab2/clock_calendar/main"},
        {.name = "Lab 2 Task 5 (unit converter)", .cli = false, .path = "lab2/converter/main"},
        {.name = "Lab 2 Task 6 (change return)", .cli = true, .path = "lab2/changer/main"},
        {.name = "Lab 3 Task 1 (auto demonstration)", .cli = false, .path = "lab3/task1/main"},
        {.name = "Lab 3 Task 2 (constexpr demonstration)", .cli = false, .path = "lab3/task2/main"},
        {.name = "Lab 3 Task 3 (range demonstration)", .cli = false, .path = "lab3/task3/main"},
        {.name = "Lab 3 Task 4 (scope demonstration)", .cli = false, .path = "lab3/task4/main"},
        {.name = "Lab 3 Task 5 (sizeof demonstration)", .cli = false, .path = "lab3/task5/main"},
        {.name = "Lab 4 Task 1 (anagram)", .cli = false, .path = "lab4/anagram/main"},
        {.name = "Lab 4 Task 2 (alphabetical order)", .cli = false, .path = "lab4/alphabet/main"},
        {.name = "Lab 4 Task 3 (todo)", .cli = true, .path = "lab4/todo/main"},
        {.name = "Lab 4 Task 4 (contact management)", .cli = true, .path = "lab4/contacts/main"},
        {.name = "Lab 4 Task 5 (text replace)", .cli = true, .path = "lab4/text_replace/main"},
        {.name = "Lab 4 Task 6 (comment stripper)",
         .cli = true,
         .path = "lab4/comment_stripper/main"},
        {.name = "Lab 5 Task 1 (containers)", .cli = false, .path = "lab5/task1/main"},
        {.name = "Lab 5 Task 2 (lambda)", .cli = false, .path = "lab5/task2/main"},
        {.name = "Lab 5 Task 3 (algorithms)", .cli = false, .path = "lab5/task3/main"},
        {.name = "Lab 5 Task 4 (numeric)", .cli = false, .path = "lab5/task4/main"},
        {.name = "Lab 5 Task 5 (vector)", .cli = false, .path = "lab5/task5/main"},
        {.name = "Lab 5 Task 6 (set)", .cli = false, .path = "lab5/task6/main"},
        {.name = "Lab 5 Task 7 (map)", .cli = false, .path = "lab5/task7/main"},
        {.name = "Lab 5 Task 8 (advanced)", .cli = false, .path = "lab5/task8/main"},
        {.name = "Lab 6 Task 1 (inventory system)", .cli = false, .path = "lab6/task1/main"},
        {.name = "Lab 6 Task 2 (bank account)", .cli = false, .path = "lab6/task2/main"},
        {.name = "Lab 6 Task 3 (employee)", .cli = false, .path = "lab6/task3/main"},
        {.name = "Lab 6 Task 4 (fraction)", .cli = false, .path = "lab6/task4/main"},
        {.name = "Lab 6 Task 5 (variant)", .cli = false, .path = "lab6/task5/main"},
        {.name = "Lab 6 Task 6 (lambda)", .cli = false, .path = "lab6/task6/main"},
        {.name = "Lab 7 Task 1 (product)", .cli = false, .path = "lab7/task1/main"},
        {.name = "Lab 7 Task 2 (shapes)", .cli = false, .path = "lab7/task2/main"},
        {.name = "Lab 7 Task 3 (filter out)", .cli = false, .path = "lab7/task3/main"},
        {.name = "Lab 7 Task 4 (contact)", .cli = false, .path = "lab7/task4/main"},
        {.name = "Lab 7 Task 5 (vector mimic)", .cli = false, .path = "lab7/task5/main"},
        {.name = "Lab 8 Task 1 (noughts and crosses)", .cli = true, .path = "lab8/task1/main"},
        {.name = "Lab 8 Task 2 (hangman)", .cli = true, .path = "lab8/task2/main"},
        {.name = "Lab 8 Task 3 (casino)", .cli = true, .path = "lab8/task3/main"},
        {.name = "Lab 8 Task 4 (battleship)", .cli = true, .path = "lab8/task4/main"},
        {.name = "Lab 8 Task 5 (puzzle)", .cli = true, .path = "lab8/task5/main"},
        {.name = "Lab 8 Task 6 (memory puzzle)", .cli = true, .path = "lab8/task6/main"},
        {.name = "Lab 9 Task 1 (mortgage)", .cli = true, .path = "lab9/task1/main"},
        {.name = "Lab 9 Task 2 (inventory)", .cli = true, .path = "lab9/task2/main"},
        {.name = "Lab 9 Task 3 (password manager)", .cli = true, .path = "lab9/task3/main"},
        {.name = "Lab 9 Task 4 (json parser)", .cli = false, .path = "lab9/task4/main"},
        {.name = "Lab 9 Task 5 (processor monitoring)", .cli = false, .path = "lab9/task5/main"},
        {.name = "Lab 9 Task 5 (family tree)", .cli = true, .path = "lab9/task6/main"},
        {.name = "Lab 10 Task 1 (text editor)", .cli = true, .path = "lab10/editor/main"},
        {.name = "Lab 10 Task 2 (traffic lights)", .cli = true, .path = "lab10/traffic/main"},
        {.name = "Lab 10 Task 3 (card system)", .cli = true, .path = "lab10/students/main"},
        {.name = "Lab 10 Task 4 (supermarket billing)",
         .cli = true,
         .path = "lab10/supermarket/main"},
        {.name = "Lab 10 Task 5 (xml parser)", .cli = false, .path = "lab10/xml/main"},
        {.name = "Lab 10 Task 6 (cli)", .cli = true, .path = "lab10/cli/main"},
        {.name = "Lab 11 Task 1 (airline)", .cli = true, .path = "lab11/task1/main"},
        {.name = "Lab 11 Task 2 (hotel)", .cli = true, .path = "lab11/task2/main"},
        {.name = "Lab 11 Task 3 (banking)", .cli = true, .path = "lab11/task3/main"},
        {.name = "Lab 11 Task 4 (stock)", .cli = true, .path = "lab11/task4/main"},
        {.name = "Lab 11 Task 5 (railway)", .cli = true, .path = "lab11/task5/main"},
        {.name = "Lab 11 Task 6 (library)", .cli = true, .path = "lab11/task6/main"},

    };

    std::cout << "Select an executable to run:\n";
    std::cout << std::left << std::setw(3) << "#" << std::setw(60) << "Name" << std::setw(30)
              << "Path" << std::setw(10) << "Has CLI?" << '\n';

    for (size_t i = 0; i < executables.size(); ++i) {
        std::cout << std::left << std::setw(3) << i << std::setw(60) << executables[i].name
                  << std::setw(30) << executables[i].path << std::setw(10)
                  << (executables[i].cli ? "YES" : "NO") << '\n';
    }

    std::cout << "Enter index: ";

    size_t choice;
    std::cin >> choice;

    if (choice >= executables.size()) {
        std::cerr << "Invalid choice\n";
        return 1;
    }

    std::string exec_path = base_path + "/" + executables[choice].path;

    const char* exec_cstr = exec_path.c_str();
    char* const argv[] = {const_cast<char*>(exec_cstr), nullptr};

    std::cout << "Launching: " << exec_cstr << "\n";

    execvp(exec_cstr, argv);

    perror("execvp failed");
    return 1;
}
