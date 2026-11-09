#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "Instruction.h"

#include <cstdint>

// 1 - Load from memory
class LoadFromMemoryInstruction : public Instruction {
private:
    int r, address;

public:
    LoadFromMemoryInstruction(const RawInstruction& raw, int r, int address);

    void execute(ExecutionContext& context) override;
    std::string describe() const override;
};

// 2 - Load immediate
class LoadImmediateInstruction : public Instruction {
private:
    int r, value;

public:
    LoadImmediateInstruction(const RawInstruction& raw, int r, int value);

    void execute(ExecutionContext& context) override;
    std::string describe() const override;
};

// 3 - Store
class StoreInstruction : public Instruction {
private:
    int r, address;

public:
    StoreInstruction(const RawInstruction& raw, int r, int address);

    void execute(ExecutionContext& context) override;
    std::string describe() const override;
};

// 4 - Move
class MoveInstruction : public Instruction {
private:
    int source, destination;

public:
    MoveInstruction(const RawInstruction& raw, int source, int destination);

    void execute(ExecutionContext& context) override;
    std::string describe() const override;
};

// 5 - Integer addition
class AddIntegerInstruction : public Instruction {
private:
    int r, s, t;

public:
    AddIntegerInstruction(const RawInstruction& raw, int r, int s, int t);

    void execute(ExecutionContext& context) override;
    std::string describe() const override;
};

// 6 - Floating-point addition
class AddFloatInstruction : public Instruction {
private:
    int r, s, t;

public:
    AddFloatInstruction(const RawInstruction& raw, int r, int s, int t);

    void execute(ExecutionContext& context) override;
    std::string describe() const override;
};

// 7 - OR
class OrInstruction : public Instruction {
private:
    int r, s, t;

public:
    OrInstruction(const RawInstruction& raw, int r, int s, int t);

    void execute(ExecutionContext& context) override;
    std::string describe() const override;
};

// 8 - AND
class AndInstruction : public Instruction {
private:
    int r, s, t;

public:
    AndInstruction(const RawInstruction& raw, int r, int s, int t);

    void execute(ExecutionContext& context) override;
    std::string describe() const override;
};

// 9 - XOR
class XorInstruction : public Instruction {
private:
    int r, s, t;

public:
    XorInstruction(const RawInstruction& raw, int r, int s, int t);

    void execute(ExecutionContext& context) override;
    std::string describe() const override;
};

// A - Rotate right
class RotateInstruction : public Instruction {
private:
    int r, count;

public:
    RotateInstruction(const RawInstruction& raw, int r, int count);

    void execute(ExecutionContext& context) override;
    std::string describe() const override;
};

// B - Conditional jump
class JumpInstruction : public Instruction {
private:
    int r, address;

public:
    JumpInstruction(const RawInstruction& raw, int r, int address);

    void execute(ExecutionContext& context) override;
    std::string describe() const override;
};

// C - Halt
class HaltInstruction : public Instruction {
public:
    explicit HaltInstruction(const RawInstruction& raw);

    void execute(ExecutionContext& context) override;
    std::string describe() const override;
};

#endif