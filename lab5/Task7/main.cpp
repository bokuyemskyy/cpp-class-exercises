#include <iostream>
#include <map>

template <typename K, typename V>
static void printMap(const std::map<K, V>& m) {
    for (const auto& pair : m) {
        std::cout << pair.first << ": " << pair.second << " ";
    }
    std::cout << "\n";
}

int main() {
    std::map<int, std::string> m;

    // insertion
    m[1] = "one";
    m[3] = "three";
    m[5] = "five";
    m[2] = "two";

    std::cout << "Map after insertion: ";
    printMap(m);

    // searching
    auto search = m.find(3);
    if (search != m.end()) {
        std::cout << "Key 3 found in the map with value: " << search->second << "\n";
    } else {
        std::cout << "Key 3 not found in the map.\n";
    }

    // deletion
    m.erase(3);
    std::cout << "Map after erasing key 3: ";
    printMap(m);

    auto it = m.find(5);
    if (it != m.end()) {
        m.erase(it);
        std::cout << "Map after erasing key 5 by iterator: ";
        printMap(m);
    }

    // other
    std::cout << "Map empty? " << (m.empty() ? "Yes" : "No") << "\n";
    std::cout << "Size of the map: " << m.size() << "\n";

    return 0;
}