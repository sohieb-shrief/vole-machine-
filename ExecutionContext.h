#ifndef EXECUTION_CONTEXT_H
#define EXECUTION_CONTEXT_H

#include "RegisterFile.h"
#include "Memory.h"

class ExecutionContext {
public:
    virtual ~ExecutionContext() = default;

    virtual RegisterFile& getRegisters() = 0;
    virtual Memory& getMemory() = 0;

    virtual void jump(int address) = 0;
    virtual void halt() = 0;
};

#endif