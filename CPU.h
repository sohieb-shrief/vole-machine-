#ifndef CPU_H
#define CPU_H

#include "ExecutionContext.h"
#include "RegisterFile.h"
#include "Memory.h"
#include "InstructionDecoder.h"
#include "CpuStatus.h"
#include "RawInstruction.h"

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