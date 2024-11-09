#ifndef TOKEN_H
#define TOKEN_H

#include <string> // for std::move

// Token types enumeration
enum TokenType { 
    ASSIGN, 
    DIVIDE, 
    END_OF_FILE, 
    IDENTIFIER, 
    LEFT_PARENTHESIS, 
    MINUS, 
    NEWLINE, 
    NUMBER, 
    PLUS, 
    RIGHT_PARENTHESIS, 
    SEMICOLON, 
    STRING, 
    TIMES, 
};

// Token structure
struct Token {
    TokenType type;  // Type of token
    int intValue;    // Value for NUMBER tokens
    std::string strValue;  // Value for STRING and IDENTIFIER tokens
    
    // Constructor for NUMBER tokens
    Token(TokenType t, int v) 
        : type(t), intValue(v), strValue("") {}
    
    // Constructor for STRING and IDENTIFIER tokens
    Token(TokenType t, std::string s) 
        : type(t), intValue(0), strValue(std::move(s)) {}
    
    // Constructor for other tokens
    Token(TokenType t) 
        : type(t), intValue(0), strValue("") {}
};

#endif
