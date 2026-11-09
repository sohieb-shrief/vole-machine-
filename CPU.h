#ifndef CPU_H
#define CPU_H

#include <string>
#include <Memory>

#include "CpuStatus.h"
#include "RawInstruction.h"
#include "ExecutionContext.h"
#include "InstructionDecoder.h"

class CPU : public ExecutionContext {
private:
    int programCounter;
    RawInstruction instructionRegister;
    CpuStatus status;
    std::string faultMessage;

    RegisterFile* registers;
    Memory* memory;

    InstructionDecoder decoder;

    RawInstruction fetch();

public:
    CPU();

    void attachHardware(RegisterFile* regFile, Memory* mem);

    CpuStatus step();
    void reset();

    void jump(int address) override;
    void halt() override;

    RegisterFile& getRegisters() override;
    Memory& getMemory() override;

    int getProgramCounter() const {
        return programCounter;
    }

    void setProgramCounter(int address);

    RawInstruction getInstructionRegister() const {
        return instructionRegister;
    }

    CpuStatus getStatus() const {
        return status;
    }

    std::string getFaultMessage() const {
        return faultMessage;
    }
};

#endif