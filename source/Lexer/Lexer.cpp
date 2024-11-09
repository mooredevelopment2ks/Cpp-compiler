#include "Lexer.h"

// Constructor implementation
Lexer::Lexer(std::istream& in) 
    : input(&in), currentChar(' ') {
    std::cout << "Lexer initialising" << '\n';
    advance(); // Initialise the first character
}

// Advance to the next character in the input stream
void Lexer::advance() {
    currentChar = input->get();
    std::cout << "Lexer: Advanced to character: " << currentChar 
        << " (int: " << static_cast<int>(currentChar) << ")" << '\n';
}

// Skip comments in the input stream
void Lexer::skipComment() {
    while (currentChar != '\n' && currentChar != EOF) {
        advance();
    }
    if (currentChar == '\n') {
        advance();
    }
}

// Handle string literals in the input stream
Token Lexer::handleString() {
    std::string strValue;
    advance(); // Skip the initial double quote
    while (currentChar != '"' && currentChar != EOF) {
        strValue += currentChar;
        advance();
    }
    if (currentChar == '"') {
        advance(); // Skip the closing double quote
    }
    std::cout << "Lexer: Token generated - STRING(" << strValue << ")" << '\n';
    return Token{ STRING, strValue };
}

// Handle identifiers in the input stream
Token Lexer::handleIdentifier() {
    std::string identifier;
    while (isalnum(currentChar) || currentChar == '_') {
        identifier += currentChar;
        advance();
    }
    std::cout << "Lexer: Token generated - IDENTIFIER(" << identifier << ")" << '\n';
    return Token{ IDENTIFIER, identifier };
}

// Get the next token from the input stream
Token Lexer::getNextToken() {
    while (currentChar != EOF) {
        // Skip whitespace except for newline
        if (isspace(currentChar) && currentChar != '\n') {
            advance();
            continue;
        }
        // Handle newline character
        if (currentChar == '\n') {
            advance();
            std::cout << "Lexer: Token generated - NEWLINE" << '\n';
            return Token{ NEWLINE  };
        }
        // Handle semicolon character
        if (currentChar == ';') {
            advance();
            std::cout << "Lexer: Token generated - SEMICOLON" << '\n';
            return Token{ SEMICOLON  };
        }
        // Handle comments starting with //
        if (currentChar == '/') {
            advance();
            if (currentChar == '/') {
                skipComment();
                continue;
            } else {
                std::cout << "Lexer: Token generated - DIVIDE" << '\n';
                return Token{ DIVIDE }; // Single / for division
            }
        }
        // Handle string literals
        if (currentChar == '"') {
            return handleString();
        }
        // Handle identifiers
        if (isalpha(currentChar) || currentChar == '_') {
            return handleIdentifier();
        }
        // Handle assignment operator
        if (currentChar == '=') {
            advance();
            std::cout << "Lexer: Token generated - ASSIGN" << '\n';
            return Token{ ASSIGN };
        }
        // Handle number tokens
        if (isdigit(currentChar)) {
            int intValue = 0;
            while (isdigit(currentChar)) {
                intValue = intValue * 10 + (currentChar - '0');
                advance();
            }
            std::cout << "Lexer: Token generated - NUMBER(" << intValue << ")" << '\n';
            return Token{ NUMBER, intValue };
        }
        // Handle plus symbol
        if (currentChar == '+') {
            advance();
            std::cout << "Lexer: Token generated - PLUS" << '\n';
            return Token{ PLUS };
        }
        // Handle minus symbol
        if (currentChar == '-') {
            advance();
            std::cout << "Lexer: Token generated - MINUS" << '\n';
            return Token{ MINUS, 0 };
        }
        // Handle times (multiplication) symbol
        if (currentChar == '*') {
            advance();
            std::cout << "Lexer: Token generated - TIMES" << '\n';
            return Token{ TIMES };
        }
        // Handle divide symbol
        if (currentChar == '/') {
            advance();
            std::cout << "Lexer: Token generated - DIVIDE" << '\n';
            return Token{ DIVIDE };
        }
        // Handle left parenthesis
        if (currentChar == '(') {
            advance();
            std::cout << "Lexer: Token generated - LEFT_PARENTHESIS" << '\n';
            return Token{ LEFT_PARENTHESIS };
        }
        // Handle right parenthesis
        if (currentChar == ')') {
            advance();
            std::cout << "Lexer: Token generated - RIGHT_PARENTHESIS" << '\n';
            return Token{ RIGHT_PARENTHESIS };
        }
    }
    // End of file token
    std::cout << "Lexer: Token generated - EOF(End Of File)" << '\n';
    return Token{ END_OF_FILE };
}
