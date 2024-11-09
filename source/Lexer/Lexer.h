#ifndef LEXER_H
#define LEXER_H

#include "Token.h"
#include <iostream>
#include <fstream>
#include <string>

// Lexer class definition
class Lexer {
private:
    std::istream* input; // Input stream
    char currentChar; // Current character being read

    // Advance to the next character
    void advance();
    // Skip comments in the input
    void skipComment();
    // Handle string literals
    Token handleString();
    // Handle identifiers
    Token handleIdentifier();

public:
    // Constructor
    Lexer(std::istream& input);
    // Get the next token from the input
    Token getNextToken();
};

#endif
