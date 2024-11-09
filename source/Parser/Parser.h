#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"
#include "SymbolTable.h"

// Parser class definition
class Parser {
private:
    Lexer lexer; // Lexer instance
    SymbolTable& symbolTable; // Symbol table reference
    Token currentToken; // Current token being parsed

    // Consume the current token and advance to the next one
    void consumeToken(TokenType type);
    // Parse a unit (number, variable, or parenthesis)
    int parseUnit();
    // Parse multiplication or division operations
    int parseMultiplicationOrDivision();
    // Parse addition or subtraction operations
    int parseAdditionOrSubtraction();
    // Handle assignments to variables
    void handleAssignment();

public:
    // Constructor
    Parser(Lexer& lexer, SymbolTable& table);
    // Process the entire input and return the final value of the last expression
    int parseAndEvaluate();
};

#endif
