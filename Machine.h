
#ifndef MACHINE_H
#define MACHINE_H

#include <string>
#include <cstdint>

#include "CPU.h"
#include "Memory.h"
#include "Screen.h"
#include "RegisterFile.h"
#include "ProgramLoader.h"
#include "CpuStatus.h"

class Machine {
private:
    Screen screen;
    Memory memory;
    RegisterFile registers;
    CPU cpu;
    ProgramLoader loader;

public:
    Machine();

    void loadProgram(const std::string& file, int start);
    void reset();

    CpuStatus step();
    int run(int maxSteps);

    void setProgramCounter(int address);

    std::uint8_t readMemory(int address);
    void writeMemory(int address, std::uint8_t value);

    std::uint8_t readRegister(int index);
    void writeRegister(int index, std::uint8_t value);

    int getProgramCounter() const;
    RawInstruction getInstructionRegister() const;

    CpuStatus getStatus() const;
    std::string getFaultMessage() const;
    std::string getScreenText() const;
};

#endif
