#include "Machine.h"

#include <iostream>
#include <string>
#include <exception>

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cout << "Usage: vole_machine <program_file> [start_address]\n";
        std::cout << "Example: vole_machine program.txt 00\n";
        return 1;
    }

    try {
        std::string fileName = argv[1];

        int startAddress = 0;

        if (argc >= 3) {
            startAddress = std::stoi(argv[2], nullptr, 16);
        }

        Machine machine;

        machine.loadProgram(fileName, startAddress);

        std::cout << "Program loaded successfully.\n";
        std::cout << "Starting execution...\n\n";

        int executed = machine.run(10000);

        std::cout << "Executed instructions: "
                  << executed << '\n';

        std::cout << "Program Counter: "
                  << std::hex << machine.getProgramCounter()
                  << '\n';

        std::cout << "Screen output: "
                  << machine.getScreenText() << '\n';

        std::cout << "Fault message: "
                  << machine.getFaultMessage() << '\n';

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
}