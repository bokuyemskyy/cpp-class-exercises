#include <math.h>
#include <stdint.h>

#include <iostream>

int g_status = 0;
/*
    declaring a global variable
    will be used in the future
*/
int main(int argc, char *argv[]) {
    // Task 1
    // some single-line comment
    /*
        some multiline comment
        bla bla bla
        some more text
    */
    // Task 2
    float f = 123.4;
    double d = 1.12345678910;
    long double ld = 0.000000000000000000001;
    // Task 3
    int index = 0;
    float shift = 10;
    char mode = 'w';
    bool active = true;
    // Task 4
    bool running = 1;
    char s = static_cast<char>(67);
    int i = -9;
    unsigned int ui = static_cast<unsigned int>((uint64_t)pow(2, 32) - 1);
    // Task 5
    /*
        in the code below I preinitialize some variables
        but for float the initialization is inside the output call
    */
    int temp = 0;
    std::cout << "[Printing]: (Pre-initialized) integer '" << temp << "' of size " << sizeof(temp)
              << std::endl;
    std::cout << "[Printing]: float '" << 6.6 << "', where the float size is " << sizeof(float)
              << std::endl;
    char ch = 'e';
    std::cout << "[Printing]: (Pre-initialized) character '" << ch << "' of size " << sizeof(ch)
              << std::endl;
    // Task 6
    void *ptr = nullptr;
    void *ptr2 = NULL;
    // Task 7
    std::cout << "The name of the file is \"" << __FILE__ << "\"" << std::endl;
    std::cout << "The compile datetime is " << __DATE__ << __TIME__ << std::endl;
    std::cout << "Current line is " << __LINE__ << ", " << std::endl;
    // Task 8
    int l_status = 1;
    std::cout << "Global int is: " << g_status << ", local int is: " << l_status << std::endl;
    // Task 9
    char c = static_cast<char>(30);
    const int x = 42;
    int *xx = const_cast<int *>(&x);
    uintptr_t addr = reinterpret_cast<uintptr_t>(xx);

    return 0;
}