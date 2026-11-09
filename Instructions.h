
#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "Instruction.h"

class LoadFromMemoryInstruction : public Instruction {
private:
    int r, address;

public:
    LoadFromMemoryInstruction(const RawInstruction& raw, int r, int address);
    void execute(ExecutionContext& context) override;
    std::string describe() const override;
};

class LoadImmediateInstruction : public Instruction {
private:
    int r, value;

public:
    LoadImmediateInstruction(const RawInstruction& raw, int r, int value);
    void execute(ExecutionContext& context) override;
    std::string describe() const override;
};

class StoreInstruction : public Instruction {
private:
    int r, address;

public:
    StoreInstruction(const RawInstruction& raw, int r, int address);
    void execute(ExecutionContext& context) override;
    std::string describe() const override;
};

class MoveInstruction : public Instruction {
private:
    int source, destination;

public:
    MoveInstruction(const RawInstruction& raw, int source, int destination);
    void execute(ExecutionContext& context) override;
    std::string describe() const override;
};

class AddIntegerInstruction : public Instruction {
private:
    int r, s, t;

public:
    AddIntegerInstruction(const RawInstruction& raw, int r, int s, int t);
    void execute(ExecutionContext& context) override;
    std::string describe() const override;
};

class AddFloatInstruction : public Instruction {
private:
    int r, s, t;

public:
    AddFloatInstruction(const RawInstruction& raw, int r, int s, int t);
    void execute(ExecutionContext& context) override;
    std::string describe() const override;
};

class OrInstruction : public Instruction {
private:
    int r, s, t;

public:
    OrInstruction(const RawInstruction& raw, int r, int s, int t);
    void execute(ExecutionContext& context) override;
    std::string describe() const override;
};

class AndInstruction : public Instruction {
private:
    int r, s, t;

public:
    AndInstruction(const RawInstruction& raw, int r, int s, int t);
    void execute(ExecutionContext& context) override;
    std::string describe() const override;
};

class XorInstruction : public Instruction {
private:
    int r, s, t;

public:
    XorInstruction(const RawInstruction& raw, int r, int s, int t);
    void execute(ExecutionContext& context) override;
    std::string describe() const override;
};

class RotateInstruction : public Instruction {
private:
    int r, count;

public:
    RotateInstruction(const RawInstruction& raw, int r, int count);
    void execute(ExecutionContext& context) override;
    std::string describe() const override;
};

class JumpInstruction : public Instruction {
private:
    int r, address;

public:
    JumpInstruction(const RawInstruction& raw, int r, int address);
    void execute(ExecutionContext& context) override;
    std::string describe() const override;
};

class HaltInstruction : public Instruction {
public:
    explicit HaltInstruction(const RawInstruction& raw);
    void execute(ExecutionContext& context) override;
    std::string describe() const override;
};

#endif
