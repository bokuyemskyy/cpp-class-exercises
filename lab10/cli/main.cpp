#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

void ls() {
    for (const auto& entry : fs::directory_iterator(fs::current_path()))
        std::cout << entry.path().filename().string() << "\n";
}

void cd(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "cd: missing argument\n";
        return;
    }
    std::error_code ec;
    fs::current_path(args[1], ec);
    if (ec) std::cerr << "cd: " << ec.message() << "\n";
}

void pwd() { std::cout << fs::current_path().string() << "\n"; }

void cat(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "cat: no filename\n";
        return;
    }
    std::ifstream file(args[1]);
    if (!file) {
        std::cerr << "cat: cannot open file\n";
        return;
    }
    std::string line;
    while (std::getline(file, line)) std::cout << line << "\n";
}

void touch(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "touch: no filename\n";
        return;
    }

    std::ofstream file(args[1], std::ios::app);
    if (!file) {
        std::cerr << "touch: cannot create file\n";
        return;
    }
}

void rm(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "rm: missing filename\n";
        return;
    }

    std::error_code ec;
    fs::path p = args[1];
    if (fs::is_directory(p, ec)) {
        std::cerr << "rm: cannot remove directory '" << p.string() << "' (use rmdir)\n";
        return;
    }

    if (!fs::remove(p, ec) || ec) {
        std::cerr << "rm: " << (ec ? ec.message() : "failed to remove file") << "\n";
    }
}


void mkdir(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "mkdir: missing directory name\n";
        return;
    }

    std::error_code ec;
    if (!fs::create_directory(args[1], ec) || ec) {
        std::cerr << "mkdir: " << (ec ? ec.message() : "failed to create directory") << "\n";
    }
}

void rmdir(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "rmdir: missing directory name\n";
        return;
    }
    std::error_code ec;
    fs::path p = args[1];
    if (!fs::is_directory(p, ec)) {
        std::cerr << "rmdir: '" << p.string() << "' is not a directory\n";
        return;
    }

    if (!fs::remove(p, ec) || ec) {
        std::cerr << "rmdir: " << (ec ? ec.message() : "failed to remove directory") << "\n";
    }
}


void echo(const std::vector<std::string>& args) {
    for (size_t i = 1; i < args.size(); ++i)
        std::cout << args[i] << (i + 1 == args.size() ? "\n" : " ");
}

void date() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);

    std::cout << std::ctime(&t);
}

void help() {
    std::cout << "Commands:\n"
                 " ls           List files\n"
                 " cd <dir>     Change directory\n"
                 " pwd          Show current directory\n"
                 " cat <file>   Show file content\n"
                 " touch <file> Create empty file\n"
                 " rm <file>    Remove file\n"
                 " mkdir <dir>  Create dir\n"
                 " rmdir <dir>  Remove dir\n"
                 " echo <text>  Print text\n"
                 " date         Showthe datetime\n"
                 " help         Show help\n"
                 " exit         Exit \n";
}

int main() {
    std::string line;
    while (true) {
        std::cin.clear(); 
        std::cin.sync(); 
        
        std::cout << "$ ";
        if (!std::getline(std::cin, line)) break;

        std::istringstream iss(line);
        std::vector<std::string> tokens;
        std::string token;

        while (iss >> token) tokens.push_back(token);
        if (tokens.empty()) continue;

        const auto& cmd = tokens[0];

        if (cmd == "exit")
            break;
        else if (cmd == "ls")
            ls();
        else if (cmd == "cd")
            cd(tokens);
        else if (cmd == "pwd")
            pwd();
        else if (cmd == "cat")
            cat(tokens);
        else if (cmd == "touch")
            touch(tokens);
        else if (cmd == "rm")
            rm(tokens);
        else if (cmd == "mkdir")
            mkdir(tokens);
        else if (cmd == "rmdir")
            rmdir(tokens);
        else if (cmd == "echo")
            echo(tokens);
        else if (cmd == "date")
            date();
        else if (cmd == "help")
            help();
        else
            std::cerr << "Unknown command: " << cmd << "\n";
    }
}
