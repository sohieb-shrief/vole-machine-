#include "InstructionDecoder.h"
#include "Instruction.h"
#include "VoleException.h"

std::unique_ptr<Instruction> InstructionDecoder::decode(const RawInstruction& raw) {
    int opcode = raw.getOpcode();
    int r = raw.getNibble(2);
    int x = raw.getNibble(3);
    int y = raw.getNibble(4);
    int xy = raw.getLowByte();
    int s = x;
    int t = y;

    switch (opcode) {
        case 1:
            return std::make_unique<LoadFromMemoryInstruction>(raw, r, xy);

        case 2:
            return std::make_unique<LoadImmediateInstruction>(raw, r, xy);

        case 3:
            return std::make_unique<StoreInstruction>(raw, r, xy);

        case 4:
            return std::make_unique<MoveInstruction>(raw, r, s);

        case 5:
            return std::make_unique<AddIntegerInstruction>(raw, r, s, t);

        case 6:
            return std::make_unique<AddFloatInstruction>(raw, r, s, t);

        case 7:
            return std::make_unique<OrInstruction>(raw, r, s, t);

        case 8:
            return std::make_unique<AndInstruction>(raw, r, s, t);

        case 9:
            return std::make_unique<XorInstruction>(raw, r, s, t);

        case 0xA:
            return std::make_unique<RotateInstruction>(raw, r, y);

        case 0xB:
            return std::make_unique<JumpInstruction>(raw, r, xy);

        case 0xC:
            if (raw.getLowByte() != 0x00 || r != 0x0) {
                throw InvalidInstructionException("Invalid HALT instruction encoding: Must be C000");
            }
            return std::make_unique<HaltInstruction>(raw);

        default:
            throw InvalidInstructionException("Unknown or Unsupported Opcode: " + std::to_string(opcode));
    }
}