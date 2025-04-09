#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <vector>
int main() {
    // ====== VECTOR ======
    std::vector<int> vec = {1, 2, 4, 8};

    vec.push_back(16);
    vec.insert(vec.end() - 2, {32, 64});

    vec.erase(vec.begin());

    auto it = std::ranges::find(vec, 4);
    if (it != vec.end()) {
        // found 4 in vec
    }

    vec.clear();

    // ====== SET ======
    std::set<double> set = {4.5, 3.2, 9.9};

    set.insert(5);
    set.insert(4.5);  // wont be added

    set.erase(9.9);

    if (set.find(4.5) != set.end()) {
        // found 4.5 in set
    }

    set.clear();

    // ====== MAP ======
    std::map<std::string, int> map;

    map["Test"] = 20;
    map["Text"] = 30;

    map.erase("Text");

    if (map.find("Test") != map.end()) {
        // found "Test" in map
        int value = map["Test"];
    }
}