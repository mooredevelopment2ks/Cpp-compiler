#include "Parser.h"
#include <iostream>
#include <fstream>

int main() {
    // Redirect input from a file
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error opening input file" << '\n';
        return 1;
    }
    std::cin.rdbuf(inputFile.rdbuf());
    std::cout << "Input file opened successfully." << '\n';

    // May throw IOException
    try {
        std::cout << "Starting initialising" << '\n';
        Parser parse;
        parse.expression();
        std::cout << "Parsing completed successfully." << '\n';
    } catch(std::exception& e) {
        std::cout << "Parser exception caught" << '\n';
        std::cout << e.what() << '\n';
    }
    std::cout << "Program finished." << '\n';
    
    return 0;
}
