#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

class FamilyTree {
    struct Person {
        std::string name;
        Person* parent = nullptr;
        std::vector<Person*> children;
        Person(std::string name) : name(std::move(name)) {}
    };

    std::map<std::string, Person*> members;

   public:
    ~FamilyTree() {
        for (auto& [name, person] : members) {
            delete person;
        }
    }

    void add(const std::string& child, const std::string& parent = "") {
        if (!members.count(child)) members[child] = new Person(child);
        if (parent.empty()) return;

        if (!members.count(parent)) members[parent] = new Person(parent);

        members[child]->parent = members[parent];
        members[parent]->children.push_back(members[child]);
    }

    void show(const std::string& name, int indent = 0) const {
        if (!members.count(name)) {
            std::cout << "Person not found\n";
            return;
        }

        auto* person = members.at(name);
        std::cout << std::string(indent * 2, ' ') << person->name << "\n";
        for (auto* child : person->children) show(child->name, indent + 1);
    }

    void save(const std::string& filename) const {
        std::ofstream out(filename);
        if (!out) {
            throw("Cant open the file\n");
        }

        for (const auto& entry : members) {
            const auto* person = entry.second;
            std::string parentName = person->parent ? person->parent->name : "root";
            out << parentName << "->" << person->name << "\n";
        }
    }

    void load(const std::string& filename) {
        std::ifstream in(filename);
        if (!in) {
            throw("Cant open the file\n");
            return;
        }

        std::string line;
        while (std::getline(in, line)) {
            std::size_t pos = line.find("->");

            std::string parent = line.substr(0, pos);
            std::string child = line.substr(pos + 2);

            add(child, parent == "root" ? "" : parent);
        }
    }
};

int main() {
    FamilyTree tree;
    std::string cmd;

    while (true) {
        std::cout << "\nCommands: add, show, save, load, exit\n> ";
        std::cin >> cmd;

        if (cmd == "add") {
            std::string parent, child;
            std::cout << "Child name: ";
            std::cin >> child;
            std::cout << "Parent name or 'none': ";
            std::cin >> parent;
            tree.add(child, parent == "none" ? "" : parent);

        } else if (cmd == "show") {
            std::string name;
            std::cout << "Root?: ";
            std::cin >> name;
            tree.show(name);

        } else if (cmd == "save") {
            std::string file;
            std::cout << "Filepath?: ";
            std::cin >> file;
            tree.save(file);
            std::cout << "Saved\n";

        } else if (cmd == "load") {
            std::string file;
            std::cout << "Filepath?: ";
            std::cin >> file;
            tree.load(file);
            std::cout << "Loaded\n";

        } else if (cmd == "exit") {
            break;

        } else {
            std::cout << "Unknown command\n";
        }
    }

    return 0;
}
