
#include "Machine.h"

#include "ProgramLoadException.h"

#include <stdexcept>
#include <string>
#include <cstdint>

Machine::Machine() {
    // Connect Memory to Screen
    memory.attachScreen(screen);

    // Connect CPU to RegisterFile and Memory
    cpu.attachHardware(&registers, &memory);
}

void Machine::loadProgram(const std::string& file, int start) {

    if (start < 0 || start >= 0xFF || start % 2 != 0) {
        throw ProgramLoadException("Invalid starting address");
    }

    // Read instructions from file
    std::vector<RawInstruction> instructions = loader.load(file);

    // Check if program fits in memory without using address FF
    if (start + static_cast<int>(instructions.size()) * 2 > 0xFF) {
        throw ProgramLoadException("Program exceeds available memory");
    }

    // Reset machine before loading new program
    reset();

    // Load complete 16-bit instructions into memory
    for (std::size_t i = 0; i < instructions.size(); i++) {

        int address = start + static_cast<int>(i) * 2;

        std::uint16_t word = static_cast<std::uint16_t>(
            std::stoul(instructions[i].toHex(), nullptr, 16)
        );

        memory.writeWord(address, word);
    }

    // Set PC to program starting address
    cpu.setProgramCounter(start);
}

void Machine::reset() {
    cpu.reset();
    registers.clear();
    memory.clear();
    screen.clear();
}

CpuStatus Machine::step() {
    return cpu.step();
}

int Machine::run(int maxSteps) {

    int executed = 0;

    while (executed < maxSteps) {

        if (cpu.getStatus() != CpuStatus::READY) {
            break;
        }

        CpuStatus result = cpu.step();

        // Count the instruction even if it was HALT or caused an error
        executed++;

        if (result != CpuStatus::READY) {
            break;
        }
    }

    return executed;
}

void Machine::setProgramCounter(int address) {
    cpu.setProgramCounter(address);
}

std::uint8_t Machine::readMemory(int address) {
    return memory.read(address);
}

void Machine::writeMemory(int address, std::uint8_t value) {
    memory.write(address, value);
}

std::uint8_t Machine::readRegister(int index) {
    return cpu.getRegisters().get(index);
}

void Machine::writeRegister(int index, std::uint8_t value) {
    cpu.getRegisters().set(index, value);
}

int Machine::getProgramCounter() const {
    return cpu.getProgramCounter();
}

RawInstruction Machine::getInstructionRegister() const {
    return cpu.getInstructionRegister();
}

CpuStatus Machine::getStatus() const {
    return cpu.getStatus();
}

std::string Machine::getFaultMessage() const {
    return cpu.getFaultMessage();
}

std::string Machine::getScreenText() const {
    return screen.getText();
}
