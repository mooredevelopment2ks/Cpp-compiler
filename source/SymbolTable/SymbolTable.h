#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <unordered_map>
#include <string>

// Symbol table class definition
class SymbolTable {
private:
    std::unordered_map<std::string, int> table; // Table storing variable names and their values

public:
    // Set the value of a variable
    void set(const std::string& name, int value);
    // Get the value of a variable
    int get(const std::string& name) const;
    // Check if a variable exists in the table
    bool contains(const std::string& name) const;
};

#endif
