#include <cmath>
#include <cstdlib>
#include "Instructions.h"
#include "VoleException.h"

#include <cstdint>
#include <sstream>
#include <string>

// Convert 8-bit floating point value to double
static double decodeFloat(uint8_t value) {
    int sign = (value & 0x80) ? -1 : 1;
    int exponent = (value >> 4) & 0x07;
    int mantissa = value & 0x0F;

    if (mantissa == 0)
        return 0.0;

    return sign * (mantissa / 16.0) *
           std::pow(2.0, exponent - 4);
}

// Convert double to 8-bit floating point value
static uint8_t encodeFloat(double value) {
    if (value == 0.0)
        return 0;

    int sign = value < 0 ? 1 : 0;
    value = std::abs(value);

    int exponent = 0;

    while (value >= 1.0 && exponent < 3) {
        value /= 2.0;
        exponent++;
    }

    while (value < 0.5 && exponent > -4) {
        value *= 2.0;
        exponent--;
    }

    int mantissa = static_cast<int>(
        std::round(value * 16.0)
    );

    if (mantissa > 15)
        mantissa = 15;

    if (mantissa < 0)
        mantissa = 0;

    int exponentBits = exponent + 4;

    return static_cast<uint8_t>(
        (sign << 7) | (exponentBits << 4) | mantissa
    );
}

// 1: Load from memory
LoadFromMemoryInstruction::LoadFromMemoryInstruction(
    const RawInstruction& raw, int r, int address)
    : Instruction(raw), r(r), address(address) {}

void LoadFromMemoryInstruction::execute(ExecutionContext& context) {
    context.getRegisters().set(
        r, context.getMemory().read(address)
    );
}

std::string LoadFromMemoryInstruction::describe() const {
    return "Load from memory";
}

// 2: Load immediate
LoadImmediateInstruction::LoadImmediateInstruction(
    const RawInstruction& raw, int r, int value)
    : Instruction(raw), r(r), value(value) {}

void LoadImmediateInstruction::execute(ExecutionContext& context) {
    context.getRegisters().set(r, static_cast<uint8_t>(value));
}

std::string LoadImmediateInstruction::describe() const {
    return "Load immediate";
}

// 3: Store
StoreInstruction::StoreInstruction(
    const RawInstruction& raw, int r, int address)
    : Instruction(raw), r(r), address(address) {}

void StoreInstruction::execute(ExecutionContext& context) {
    context.getMemory().write(
        address, context.getRegisters().get(r)
    );
}

std::string StoreInstruction::describe() const {
    return "Store";
}

// 4: Move
MoveInstruction::MoveInstruction(
    const RawInstruction& raw, int source, int destination)
    : Instruction(raw), source(source), destination(destination) {}

void MoveInstruction::execute(ExecutionContext& context) {
    uint8_t value = context.getRegisters().get(source);
    context.getRegisters().set(destination, value);
}

std::string MoveInstruction::describe() const {
    return "Move";
}

// 5: Integer addition
AddIntegerInstruction::AddIntegerInstruction(
    const RawInstruction& raw, int r, int s, int t)
    : Instruction(raw), r(r), s(s), t(t) {}

void AddIntegerInstruction::execute(ExecutionContext& context) {
    int a = static_cast<int8_t>(
        context.getRegisters().get(s)
    );

    int b = static_cast<int8_t>(
        context.getRegisters().get(t)
    );

    int result = a + b;

    context.getRegisters().set(
        r, static_cast<uint8_t>(result)
    );
}

std::string AddIntegerInstruction::describe() const {
    return "Integer addition";
}

// 6: Floating point addition
AddFloatInstruction::AddFloatInstruction(
    const RawInstruction& raw, int r, int s, int t)
    : Instruction(raw), r(r), s(s), t(t) {}

void AddFloatInstruction::execute(ExecutionContext& context) {
    double a = decodeFloat(
        context.getRegisters().get(s)
    );

    double b = decodeFloat(
        context.getRegisters().get(t)
    );

    uint8_t result = encodeFloat(a + b);

    context.getRegisters().set(r, result);
}

std::string AddFloatInstruction::describe() const {
    return "Floating point addition";
}

// 7: OR
OrInstruction::OrInstruction(
    const RawInstruction& raw, int r, int s, int t)
    : Instruction(raw), r(r), s(s), t(t) {}

void OrInstruction::execute(ExecutionContext& context) {
    uint8_t result =
        context.getRegisters().get(s) |
        context.getRegisters().get(t);

    context.getRegisters().set(r, result);
}

std::string OrInstruction::describe() const {
    return "OR";
}

// 8: AND
AndInstruction::AndInstruction(
    const RawInstruction& raw, int r, int s, int t)
    : Instruction(raw), r(r), s(s), t(t) {}

void AndInstruction::execute(ExecutionContext& context) {
    uint8_t result =
        context.getRegisters().get(s) &
        context.getRegisters().get(t);

    context.getRegisters().set(r, result);
}

std::string AndInstruction::describe() const {
    return "AND";
}

// 9: XOR
XorInstruction::XorInstruction(
    const RawInstruction& raw, int r, int s, int t)
    : Instruction(raw), r(r), s(s), t(t) {}

void XorInstruction::execute(ExecutionContext& context) {
    uint8_t result =
        context.getRegisters().get(s) ^
        context.getRegisters().get(t);

    context.getRegisters().set(r, result);
}

std::string XorInstruction::describe() const {
    return "XOR";
}

// A: Rotate right
RotateInstruction::RotateInstruction(
    const RawInstruction& raw, int r, int count)
    : Instruction(raw), r(r), count(count) {}

void RotateInstruction::execute(ExecutionContext& context) {
    uint8_t value = context.getRegisters().get(r);

    count %= 8;

    if (count < 0)
        count += 8;

    if (count != 0) {
        value = static_cast<uint8_t>(
            (value >> count) |
            (value << (8 - count))
        );
    }

    context.getRegisters().set(r, value);
}

std::string RotateInstruction::describe() const {
    return "Rotate right";
}

// B: Jump
JumpInstruction::JumpInstruction(
    const RawInstruction& raw, int r, int address)
    : Instruction(raw), r(r), address(address) {}

void JumpInstruction::execute(ExecutionContext& context) {
    if (context.getRegisters().get(r) ==
        context.getRegisters().get(0)) {
        context.jump(address);
    }
}

std::string JumpInstruction::describe() const {
    return "Conditional jump";
}

// C: Halt
HaltInstruction::HaltInstruction(const RawInstruction& raw)
    : Instruction(raw) {}

void HaltInstruction::execute(ExecutionContext& context) {
    context.halt();
}

std::string HaltInstruction::describe() const {
    return "Halt";
}
