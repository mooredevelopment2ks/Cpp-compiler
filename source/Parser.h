#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <exception> // for std::exception
#include <stdexcept> // for std::runtime_error
#include <cctype> // for std::isdigit, std::isspace

class Parser {
    public:
        static int lookahead;

        Parser(); // Constructor
        void match(int t);
        void term();
        void expression();
        void skipWhitespace();
};

#endif
