#include "Parser.h"
#include "SymbolTable.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <dirent.h>

// Function to get files with the .newLang extension in a directory
std::vector<std::string> getNewLangFiles(const std::string& path) {
    std::vector<std::string> files;
    DIR* openDirectory = opendir(path.c_str()); // Open the specified directory
    if (openDirectory == nullptr) {
        std::cerr << "Failed to open directory: " << path << '\n';
        return files;
    }
    struct dirent* directoryPointer;
    while ((directoryPointer = readdir(openDirectory)) != nullptr) {
        std::string filename = directoryPointer->d_name; // d_name is the filename in the struct
        std::cout << "Found file: " << filename << '\n';
        /* Check if the filename ends with the .newLang extension 
        and does not start with a dot because I had issues with .vscode directory */
        if (filename.rfind(".newLang") == (filename.length() - 8) && filename[0] != '.') {
            files.push_back(path + "/" + filename);
        }
    }
    closedir(openDirectory); // Close the directory
    return files;
}

int main() {
    std::vector<std::string> files;

    // Added both searches due to running the program in different directories
    // Search in the parent directory and all files with the .newLang extension
    std::vector<std::string> parentFiles = getNewLangFiles("..");
    files.insert(files.end(), parentFiles.begin(), parentFiles.end());

    // Search in the current directory and all files with the .newLang extension
    std::vector<std::string> currentFiles = getNewLangFiles(".");
    files.insert(files.end(), currentFiles.begin(), currentFiles.end());

    if (files.empty()) {
        std::cerr << "No files with .newLang extension found in the specified directory." << '\n';
        return 1;
    }

    std::string filename = files[0]; // Use the first file found
    std::cout << "Trying to open file: " << filename << '\n';
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Error opening input file: " << filename << '\n';
        return 1;
    }

    std::cout << "Input file " << filename << " opened successfully." << '\n';

    SymbolTable symbolTable; // Create a symbol table
    Lexer lexer(inputFile); // Create a lexer with the input file
    Parser parser(lexer, symbolTable); // Create a parser with the lexer and symbol table

    try {
        int lastExpressionValue = parser.parseAndEvaluate(); // Call parseAndEvaluate and return final result
        std::cout << "Last expression value: " << lastExpressionValue << '\n';
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << '\n';
    }

    std::cout << "Program finished." << '\n';
    return 0;
}
