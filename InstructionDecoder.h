#ifndef INSTRUCTION_DECODER_H
#define INSTRUCTION_DECODER_H

#include <Memory>
#include "RawInstruction.h"

class Instruction;

class InstructionDecoder {
public:
    InstructionDecoder() = default;

    std::unique_ptr<Instruction> decode(const RawInstruction& raw);
};

#endif 