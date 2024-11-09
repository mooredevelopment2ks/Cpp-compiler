#include "SymbolTable.h"
#include <stdexcept>

// Set the value of a variable
void SymbolTable::set(const std::string& name, int value) {
    table[name] = value;
}

// Get the value of a variable
int SymbolTable::get(const std::string& name) const {
    auto it = table.find(name);
    if (it != table.end()) {
        return it->second;
    }
    throw std::runtime_error("Undefined variable: " + name);
}

// Check if a variable exists in the table
bool SymbolTable::contains(const std::string& name) const {
    return table.find(name) != table.end();
}
