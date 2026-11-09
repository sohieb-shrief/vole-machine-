#ifndef CPU_H
#define CPU_H

#include <string>
#include <memory>
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

    class RegisterFile* registers;
    class Memory* memory;
    InstructionDecoder decoder;

    RawInstruction fetch();

public:
    CPU();
    void attachHardware(class RegisterFile* regFile, class Memory* mem);

    CpuStatus step();
    void reset();

    void jump(int address) override;
    void halt() override;
    class RegisterFile* getRegisters() override { return registers; }
    class Memory* getMemory() override { return memory; }

    int getProgramCounter() const { return programCounter; }
    void setProgramCounter(int address);
    RawInstruction getInstructionRegister() const { return instructionRegister; }
    CpuStatus getStatus() const { return status; }
    std::string getFaultMessage() const { return faultMessage; }
};

#endif 