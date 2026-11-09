#include "InstructionDecoder.h"
#include "Instructions.h"
#include "VoleException.h"

#include <string>

std::unique_ptr<Instruction> InstructionDecoder::decode(
    const RawInstruction& raw) {

    int opcode = raw.getOpcode();

    int r = raw.getNibble(2);
    int x = raw.getNibble(3);
    int y = raw.getNibble(4);

    int xy = raw.getLowByte();

    switch (opcode) {

    case 0x1:
        return std::make_unique<LoadFromMemoryInstruction>(
            raw, r, xy);

    case 0x2:
        return std::make_unique<LoadImmediateInstruction>(
            raw, r, xy);

    case 0x3:
        return std::make_unique<StoreInstruction>(
            raw, r, xy);

    case 0x4:
        if (r != 0) {
            throw InvalidInstructionException(
                "Invalid MOVE instruction: second digit must be 0");
        }

        return std::make_unique<MoveInstruction>(
            raw, x, y);

    case 0x5:
        return std::make_unique<AddIntegerInstruction>(
            raw, r, x, y);

    case 0x6:
        return std::make_unique<AddFloatInstruction>(
            raw, r, x, y);

    case 0x7:
        return std::make_unique<OrInstruction>(
            raw, r, x, y);

    case 0x8:
        return std::make_unique<AndInstruction>(
            raw, r, x, y);

    case 0x9:
        return std::make_unique<XorInstruction>(
            raw, r, x, y);

    case 0xA:
        if (x != 0) {
            throw InvalidInstructionException(
                "Invalid ROTATE instruction: third digit must be 0");
        }

        return std::make_unique<RotateInstruction>(
            raw, r, y);

    case 0xB:
        return std::make_unique<JumpInstruction>(
            raw, r, xy);

    case 0xC:
        if (raw.getWord() != 0xC000) {
            throw InvalidInstructionException(
                "Invalid HALT instruction: expected C000");
        }

        return std::make_unique<HaltInstruction>(raw);

    default:
        throw InvalidInstructionException(
            "Unknown opcode: " + std::to_string(opcode));
    }
}