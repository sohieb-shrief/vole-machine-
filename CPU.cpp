#include "CPU.h"
#include "RegisterFile.h"
#include "Memory.h"
#include "Instruction.h"
#include "VoleException.h"

CPU::CPU() 
    : programCounter(0), status(CpuStatus::READY), faultMessage(""), registers(nullptr), memory(nullptr) {}

void CPU::attachHardware(RegisterFile* regFile, Memory* mem) {
    this->registers = regFile;
    this->memory = mem;
}

void CPU::reset() {
    programCounter = 0;
    instructionRegister = RawInstruction(0);
    status = CpuStatus::READY;
    faultMessage = "";
}

void CPU::setProgramCounter(int address) {
    if (address < 0 || address > 0xFE || address % 2 != 0) {
        status = CpuStatus::INVALID_PC;
        faultMessage = "Invalid Program Counter address: Must be even and <= FE";
        throw InvalidAddressException(faultMessage);
    }
    programCounter = address;
}

RawInstruction CPU::fetch() {
    if (!memory) {
        throw VoleException("Memory not attached to CPU!");
    }

    if (programCounter < 0 || programCounter > 0xFE) {
        status = CpuStatus::INVALID_PC;
        faultMessage = "PC out of bounds during fetch phase: " + std::to_string(programCounter);
        throw InvalidAddressException(faultMessage);
    }

    int highByte = static_cast<unsigned char>(memory->read(programCounter));
    int lowByte = static_cast<unsigned char>(memory->read(programCounter + 1));
    
    int rawWord = (highByte << 8) | lowByte;

    programCounter += 2;

    return RawInstruction(rawWord);
}

CpuStatus CPU::step() {
    if (status == CpuStatus::HALTED) {
        return status;
    }

    try {
        instructionRegister = fetch();

        std::unique_ptr<Instruction> instruction = decoder.decode(instructionRegister);

        instruction->execute(*this);

        if (status != CpuStatus::HALTED) {
            status = CpuStatus::READY;
        }
    } 
    catch (const InvalidInstructionException& e) {
        status = CpuStatus::INVALID_INSTRUCTION;
        faultMessage = e.what();
    } 
    catch (const InvalidAddressException& e) {
        status = CpuStatus::INVALID_PC;
        faultMessage = e.what();
    } 
    catch (const VoleException& e) {
        status = CpuStatus::INVALID_INSTRUCTION;
        faultMessage = e.what();
    }

    return status;
}

void CPU::jump(int address) {
    setProgramCounter(address);
}

void CPU::halt() {
    status = CpuStatus::HALTED;
}