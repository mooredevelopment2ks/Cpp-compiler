#include "Parser.h"

/* Static Member Initialisation: Static members 
must be defined outside the class definition. 
Ensure lookahead is defined in a source file.
Definition of static member in this cpp file */
int Parser::lookahead{0};

// May throw IOException
// Constructor
Parser::Parser() {
    lookahead = std::cin.get();
    skipWhitespace();
    std::cout << "Parser initialised with lookahead: " << static_cast<char>(lookahead) << '\n';
}

// May throw IOException
// Match function
void Parser::match(int t) {
    if (lookahead == t) {
        std::cout << "Matched token: " << static_cast<char>(lookahead) << '\n';
        lookahead = std::cin.get(); // Get the next token
        skipWhitespace();
        std::cout << "Next lookahead: " << static_cast<char>(lookahead) << '\n';
    } else {
        std::cout << "Expected token: " << static_cast<char>(t) << ", but found: " << static_cast<char>(lookahead) << '\n';
        throw std::runtime_error("syntax error");
    }
}

// May throw IOException
// Term function
void Parser::term() {
    if (std::isdigit(static_cast<char>(lookahead))) {
        std::cout << "Term tokens: ";
        while (std::isdigit(static_cast<char>(lookahead))) {
            std::cout << static_cast<char>(lookahead);
            lookahead = std::cin.get();
        }
        std::cout << '\n';
        skipWhitespace();
    } else {
        std::cout << "Expected digit, but found: " << static_cast<char>(lookahead) << '\n';
        throw std::runtime_error("syntax error");
    }
}

// May throw IOException
// Expression function
void Parser::expression() {
    try {
        term();
        while (true) {
            if (lookahead == '+') {
                match('+');
                term();
            } else if (lookahead == '-') {
                match('-');
                term();
            } else if (lookahead == EOF) {
                return;
            } else {
                return;
            }
        }
    } catch (const std::runtime_error& e) {
        std::cout << "Parser exception caught: " << e.what() << '\n';
    }
}

// Skip whitespace function
void Parser::skipWhitespace() {
    while (std::isspace(static_cast<char>(lookahead)) && lookahead != EOF) {
        lookahead = std::cin.get();
    }
    std::cout << "Whitespace skipped, next lookahead: " << static_cast<char>(lookahead) << '\n';
}
