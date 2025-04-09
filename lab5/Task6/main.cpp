#include <iostream>
#include <set>

template <typename T>
static void printSet(const std::set<T>& s) {
    for (const T& elem : s) {
        std::cout << elem << " ";
    }
    std::cout << "\n";
}

int main() {
    std::set<int> s;

    // insertion
    s.insert(5);
    s.insert(3);
    s.insert(7);
    s.insert(1);

    std::cout << "Set after insertion: ";
    printSet(s);

    // searching
    auto search = s.find(3);
    if (search != s.end()) {
        std::cout << "Element 3 found in the set.\n";
    } else {
        std::cout << "Element 3 not found in the set.\n";
    }

    // deletion
    s.erase(3);
    std::cout << "Set after erasing 3: ";
    printSet(s);

    auto it = s.find(7);
    if (it != s.end()) {
        s.erase(it);
        std::cout << "Set after erasing element 7 by iterator: ";
        printSet(s);
    }

    // other
    std::cout << "Set empty? " << (s.empty() ? "Yes" : "No") << "\n";
    std::cout << "Size of the set: " << s.size() << "\n";

    return 0;
}