
#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "ExecutionContext.h"
#include "RawInstruction.h"
#include <string>

class Instruction {
protected:
    RawInstruction raw;

public:
    explicit Instruction(const RawInstruction& instruction)
        : raw(instruction) {}

    virtual ~Instruction() = default;

    virtual void execute(ExecutionContext& context) = 0;

    virtual std::string describe() const = 0;
};

#endif
