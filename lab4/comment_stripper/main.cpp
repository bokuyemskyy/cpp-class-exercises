#include <fstream>
#include <iostream>
#include <string>

std::string stripComments(const std::string &code) {
  std::string result;
  bool inString = false, inChar = false, inLineComment = false,
       inBlockComment = false;

  for (size_t i = 0; i < code.size(); ++i) {
    char c = code[i];
    char next = (i + 1 < code.size()) ? code[i + 1] : '\0';

    if (inLineComment && c == '\n') {
      inLineComment = false;
      result += c;
    } else if (inBlockComment && c == '*' && next == '/') {
      inBlockComment = false;
      ++i;
    } else if (inLineComment || inBlockComment) {
      continue;
    } else if (!inString && !inChar && c == '/' && next == '/') {
      inLineComment = true;
      ++i;
    } else if (!inString && !inChar && c == '/' && next == '*') {
      inBlockComment = true;
      ++i;
    } else {
      result += c;
      if (c == '"' && !inChar && (i == 0 || code[i - 1] != '\\'))
        inString = !inString;
      if (c == '\'' && !inString && (i == 0 || code[i - 1] != '\\'))
        inChar = !inChar;
    }
  }

  return result;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <file.cpp/.h>\n";
    return 1;
  }

  std::ifstream inFile(argv[1]);
  if (!inFile) {
    std::cerr << "Error opening file.\n";
    return 1;
  }

  std::string code((std::istreambuf_iterator<char>(inFile)), {});
  std::cout << stripComments(code);
  return 0;
}
