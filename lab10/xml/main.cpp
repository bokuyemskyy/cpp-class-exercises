#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct XMLNode {
    std::string tag;
    std::string content;
    std::vector<XMLNode> children;
};

class XMLParser {
    std::string data;
    size_t pos = 0;

    void skipWhitespace() {
        while (pos < data.size() && isspace(data[pos])) pos++;
    }

    bool startsWith(const std::string& s) { return data.compare(pos, s.size(), s) == 0; }

    std::string parseTagName() {
        size_t start = pos;
        while (pos < data.size() && (isalnum(data[pos]) || data[pos] == ':' || data[pos] == '-'))
            pos++;
        return data.substr(start, pos - start);
    }

    XMLNode parseNode() {
        XMLNode node;
        if (data[pos] != '<') throw "Expected <";
        pos++;
        node.tag = parseTagName();
        skipWhitespace();

        if (data[pos] == '>') {
            pos++;

            std::stringstream contentStream;
            while (true) {
                skipWhitespace();
                if (pos >= data.size()) throw "Unexpected end of data";

                if (startsWith("</" + node.tag + ">")) {
                    pos += 3 + node.tag.size();
                    break;
                } else if (data[pos] == '<') {
                    if (data[pos + 1] == '/') {
                        throw "Wrong closing tag";
                    }
                    XMLNode child = parseNode();
                    node.children.push_back(child);
                } else {
                    size_t start = pos;
                    while (pos < data.size() && data[pos] != '<') pos++;
                    contentStream << data.substr(start, pos - start);
                }
            }
            node.content = contentStream.str();
        } else if (data[pos] == '/' && data[pos + 1] == '>') {
            pos += 2;
        } else {
            throw "Unexpected character after tag name";
        }
        return node;
    }

   public:
    XMLNode parse(const std::string& input) {
        data = input;
        pos = 0;
        skipWhitespace();
        return parseNode();
    }
};

void printXML(const XMLNode& node, int indent = 0) {
    std::string space(indent, ' ');
    std::cout << space << "<" << node.tag << ">";

    if (!node.content.empty()) std::cout << node.content;

    std::cout << "\n";

    for (const auto& child : node.children) printXML(child, indent + 2);
    std::cout << space << "</" << node.tag << ">\n";
}

int main(int argc, char* argv[]) {
    std::string filepath;
    std::cout << "Enter XML filepath: ";
    std::getline(std::cin, filepath);

    std::ifstream file(filepath);
    if (!file) {
        std::cerr << "Cant open file\n";
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    XMLParser parser;
    try {
        XMLNode root = parser.parse(content);
        printXML(root);
    } catch (const std::exception& e) {
        std::cerr << "An error appeared: " << e.what() << "\n";
        return 1;
    }
}
