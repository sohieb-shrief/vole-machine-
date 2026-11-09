
#include "ProgramLoader.h"
#include "ProgramLoadException.h"

#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <vector>

std::vector<RawInstruction> ProgramLoader::load(const std::string& file)
{
    std::ifstream input(file);

    if (!input.is_open()) {
        throw ProgramLoadException("Cannot open program file");
    }

    std::vector<RawInstruction> instructions;
    std::string line;

    while (std::getline(input, line))
    {
        // Remove comments
        size_t comment = line.find(';');

        if (comment != std::string::npos) {
            line = line.substr(0, comment);
        }

        // Read the first word
        std::stringstream ss(line);
        std::string word;

        if (!(ss >> word)) {
            continue;
        }

        // Check instruction length
        if (word.length() != 4) {
            throw ProgramLoadException(
                "Invalid instruction length: " + word
            );
        }

        // Check hexadecimal characters
        for (char c : word)
        {
            if (!std::isxdigit(static_cast<unsigned char>(c))) {
                throw ProgramLoadException(
                    "Invalid hexadecimal instruction: " + word
                );
            }
        }

        // Convert hexadecimal to integer
        int value = std::stoi(word, nullptr, 16);

        instructions.push_back(RawInstruction(value));
    }

    if (input.bad()) {
        throw ProgramLoadException("Error while reading program file");
    }

    if (instructions.empty()) {
        throw ProgramLoadException("Program file is empty");
    }

    return instructions;
}
