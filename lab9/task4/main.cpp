#include <cctype>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

class JSONValue {
   public:
    virtual ~JSONValue() {}
    [[nodiscard]] virtual std::string toString() const = 0;
};

class JSONString : public JSONValue {
    std::string m_value;

   public:
    JSONString(std::string value) : m_value(std::move(value)) {}
    [[nodiscard]] std::string toString() const override { return "\"" + m_value + "\""; }
    [[nodiscard]] const std::string& get() const { return m_value; }
};
class JSONNumber : public JSONValue {
    double m_value;

   public:
    JSONNumber(double value) : m_value(value) {}
    [[nodiscard]] std::string toString() const override { return std::to_string(m_value); }
    [[nodiscard]] double get() const { return m_value; }
};

class JSONBoolean : public JSONValue {
    bool m_value;

   public:
    JSONBoolean(bool value) : m_value(value) {}
    [[nodiscard]] std::string toString() const override { return m_value ? "true" : "false"; }
    [[nodiscard]] bool get() const { return m_value; }
};

class JSONNull : public JSONValue {
   public:
    JSONNull() {}
    [[nodiscard]] std::string toString() const override { return "null"; }
};

class JSONObject : public JSONValue {
    std::map<std::string, JSONValue*> m_values;

   public:
    ~JSONObject() {
        for (auto& value : m_values) delete value.second;
    }
    void add(const std::string& key, JSONValue* value) { m_values[key] = value; }
    [[nodiscard]] std::string toString() const override {
        std::string res = "{";
        bool first = true;
        for (const auto& value : m_values) {
            if (!first) res += ",";
            res += "\"" + value.first + "\":" + value.second->toString();
            first = false;
        }
        res += "}";
        return res;
    }
};
class JSONArray : public JSONValue {
    std::vector<JSONValue*> m_values;

   public:
    ~JSONArray() {
        for (auto& value : m_values) delete value;
    }
    void add(JSONValue* value) { m_values.push_back(value); }
    [[nodiscard]] std::string toString() const override {
        std::string res = "[";
        bool first = true;
        for (const auto& value : m_values) {
            if (!first) res += ",";
            res += value->toString();
            first = false;
        }
        res += "]";
        return res;
    }
};

class JSONParser {
    const std::string& input;
    size_t pos;

   public:
    JSONParser(const std::string& string) : input(string), pos(0) {}
    void skipSpace() {
        while (pos < input.size() && isspace(input[pos])) pos++;
    }
    char peek() {
        if (pos < input.size()) return input[pos];
        return '\0';
    }
    char get() {
        if (pos < input.size()) return input[pos++];
        throw("Unexpected end of input");
    }
    JSONValue* parseValue() {
        skipSpace();
        char c = peek();
        if (c == '{')
            return parseObject();
        else if (c == '[')
            return parseArray();
        else if (c == '"')
            return parseString();
        else if (c == 't' || c == 'f')
            return parseBoolean();
        else if (c == 'n')
            return parseNull();
        else if (c == '-' || isdigit(c))
            return parseNumber();
        else
            throw("Invalid JSON");
    }

    JSONObject* parseObject() {
        if (get() != '{') throw std::runtime_error("Expected '{'");

        auto* obj = new JSONObject();

        skipSpace();
        if (peek() == '}') {
            get();
            return obj;
        }

        while (true) {
            skipSpace();
            if (peek() != '"') {
                delete obj;
                throw("Expected '\"' as a key");
            }
            JSONString* key = parseString();

            skipSpace();
            if (get() != ':') {
                delete key;
                delete obj;
                throw("Expected ':' after key");
            }

            JSONValue* value = parseValue();

            obj->add(key->get(), value);
            delete key;

            skipSpace();
            char c = get();
            if (c == '}') break;
            if (c != ',') {
                delete obj;
                throw("Expected ',' or '}'");
            }
        }
        return obj;
    }

    JSONArray* parseArray() {
        if (get() != '[') throw("Expected '['");

        auto* arr = new JSONArray();

        skipSpace();
        if (peek() == ']') {
            get();
            return arr;
        }

        while (true) {
            JSONValue* val = parseValue();
            arr->add(val);

            skipSpace();
            char c = get();
            if (c == ']') break;
            if (c != ',') {
                delete arr;
                throw("Expected ',' or ']'");
            }
        }
        return arr;
    }

    JSONString* parseString() {
        if (get() != '"') throw("Expected '\"'");

        std::string result;
        while (true) {
            if (pos >= input.size()) throw("Unterminated string");

            char c = get();
            if (c == '"') break;
            result += c;
        }
        return new JSONString(result);
    }

    JSONValue* parseNumber() {
        skipSpace();
        size_t start = pos;

        if (peek() == '-') get();

        if (!isdigit(peek())) throw("Invalid number");

        while (isdigit(peek())) get();

        if (peek() == '.') {
            get();
            if (!isdigit(peek())) throw("Invalid number");
            while (isdigit(peek())) get();
        }

        if (peek() == 'e' || peek() == 'E') {
            get();
            if (peek() == '+' || peek() == '-') get();
            if (!isdigit(peek())) throw("Invalid number");
            while (isdigit(peek())) get();
        }

        std::string numStr = input.substr(start, pos - start);
        char* endPtr = nullptr;
        double val = strtod(numStr.c_str(), &endPtr);
        if (endPtr != numStr.c_str() + numStr.size()) throw("Invalid number");

        return new JSONNumber(val);
    }

    JSONBoolean* parseBoolean() {
        if (input.compare(pos, 4, "true") == 0) {
            pos += 4;
            return new JSONBoolean(true);
        } else if (input.compare(pos, 5, "false") == 0) {
            pos += 5;
            return new JSONBoolean(false);
        } else
            throw("Invalid boolean value");
    }

    JSONNull* parseNull() {
        if (input.compare(pos, 4, "null") == 0) {
            pos += 4;
            return new JSONNull();
        } else
            throw("Invalid null value");
    }
};

int main() {
    std::string jsonText = R"({
        "name": "Ivan",
        "age": 18,
        "student": true,
        "hobbies": ["hobby1", "hobby2"],
        "address": null
    })";

    JSONParser parser(jsonText);
    JSONValue* value = parser.parseValue();
    std::cout << value->toString() << "\n";
    delete value;

    return 0;
}
