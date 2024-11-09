#include "Parser.h"
#include <stdexcept>

// Constructor implementation
Parser::Parser(Lexer& lex, SymbolTable& table) 
    : lexer(lex), symbolTable(table), currentToken(lexer.getNextToken()) {
        std::cout << "Parser initialising" << '\n';
}

// Consume the current token and advance to the next one
void Parser::consumeToken(TokenType type) {
    std::cout << "Parser: Consuming token of type " << type << '\n';
    if (currentToken.type == type) {
        currentToken = lexer.getNextToken();
    } else {
        throw std::runtime_error("Syntax error");
    }
}

// Parse a unit (number, variable, string, or parenthesis)
// Parentheses have the highest precedence and are evaluated first
int Parser::parseUnit() {
    if (currentToken.type == NUMBER) {
        Token token = currentToken;
        std::cout << "Parser: Processing unit with token value " << token.intValue << '\n';
        consumeToken(NUMBER);
        return token.intValue;
    } else if (currentToken.type == IDENTIFIER) {
        std::string variableName = currentToken.strValue;
        consumeToken(IDENTIFIER);
        if (currentToken.type == ASSIGN) {
            consumeToken(ASSIGN);
            int value = parseAdditionOrSubtraction();
            symbolTable.set(variableName, value);
            return value;
        } else if (symbolTable.contains(variableName)) { // Check if variable exists in symbol table
            return symbolTable.get(variableName);
        } else {
            return symbolTable.get(variableName);
        }
    } else if (currentToken.type == STRING) {
        std::string strValue = currentToken.strValue;
        consumeToken(STRING);
        std::cout << "Parser: Processing string with value \"" << strValue << "\"" << '\n';
        return 0; // Return a default value for string tokens
    } else if (currentToken.type == LEFT_PARENTHESIS) {
        consumeToken(LEFT_PARENTHESIS);
        int result = parseAdditionOrSubtraction(); // Evaluate the expression inside the parentheses first
        consumeToken(RIGHT_PARENTHESIS);
        return result; // Return the result of the parenthesized expression
    } else {
        throw std::runtime_error("Syntax error: Expected number, variable, string, or parenthesis");
    }
}

// Parse multiplication or division operations
// This function ensures multiplication and division are evaluated before addition and subtraction
int Parser::parseMultiplicationOrDivision() {
    int result = parseUnit(); // Start with the primitive unit (number, variable, or parenthesis)
    while (currentToken.type == TIMES || currentToken.type == DIVIDE) {
        if (currentToken.type == TIMES) {
            consumeToken(TIMES);
            result *= parseUnit(); // Continue to parse the next primitive unit
        } else if (currentToken.type == DIVIDE) {
            consumeToken(DIVIDE);
            result /= parseUnit(); // Continue to parse the next primitive unit
        }
    }
    return result; // Return the evaluated result of multiplication or division operations
}

// Parse addition or subtraction operations
// This function ensures addition and subtraction are evaluated after multiplication and division
int Parser::parseAdditionOrSubtraction() {
    int result = parseMultiplicationOrDivision(); // Start with the result of multiplication or division
    while (currentToken.type == PLUS || currentToken.type == MINUS) {
        if (currentToken.type == PLUS) {
            consumeToken(PLUS);
            result += parseMultiplicationOrDivision(); // Continue to parse the next multiplication or division
        } else if (currentToken.type == MINUS) {
            consumeToken(MINUS);
            result -= parseMultiplicationOrDivision(); // Continue to parse the next multiplication or division
        }
    }
    return result; 
}

// Handle assignments to variables
void Parser::handleAssignment() {
    if (currentToken.type == IDENTIFIER) {
        std::string variableName = currentToken.strValue;
        consumeToken(IDENTIFIER);
        consumeToken(ASSIGN);
        int value = parseAdditionOrSubtraction(); // Parse the expression on the right-hand side of the assignment
        symbolTable.set(variableName, value); // Store the result in the symbol table
        std::cout << "Parser: Assigned " << value << " to variable " << variableName << '\n'; // Include the variable name in the output
    } else {
        throw std::runtime_error("Syntax error: Expected variable name");
    }
}



// Process the entire input and return the final value of the last expression
int Parser::parseAndEvaluate() {
    int lastExpressionValue = 0;  // Initialize final value
    while (currentToken.type != END_OF_FILE) {
        if (currentToken.type == NEWLINE || currentToken.type == SEMICOLON) {
            consumeToken(currentToken.type);
            continue; // Skip to the next token
        } else if (currentToken.type == IDENTIFIER) {
            handleAssignment();
            if (currentToken.type == SEMICOLON) { // Consume semicolon after expression
                std::cout << "Parser: Found semicolon after handleAssignment" << '\n';
                consumeToken(currentToken.type);
            }
            continue; // Handle assignments
        } else if (currentToken.type == STRING) {
            std::cout << "Parser: Ignoring string with value \"" << currentToken.strValue << "\"" << '\n';
            consumeToken(STRING);
            continue; // Skip to the next token
        } else {
            // TODO: Handle other potential cases or future functionality
            std::cerr << "Parser: Unexpected token type" << '\n';
            consumeToken(currentToken.type);
        }
    }
    std::cout << "Parser: Found END_OF_FILE" << '\n';
    return lastExpressionValue;  // Return the final value of the last expression
}
