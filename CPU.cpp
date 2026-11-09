#include "CPU.h"
#include "RegisterFile.h"
#include "Memory.h"
#include "Instruction.h"
#include "VoleException.h"

#include <stdexcept>
#include <string>

CPU::CPU()
    : programCounter(0),
      instructionRegister(0),
      status(CpuStatus::READY),
      faultMessage(""),
      registers(nullptr),
      memory(nullptr) {
}

void CPU::attachHardware(RegisterFile* regFile, Memory* mem) {
    if (regFile == nullptr || mem == nullptr) {
        throw VoleException("Cannot attach null hardware to CPU!");
    }

    registers = regFile;
    memory = mem;
}

RegisterFile& CPU::getRegisters() {
    if (registers == nullptr) {
        throw VoleException("RegisterFile not attached to CPU!");
    }

    return *registers;
}

Memory& CPU::getMemory() {
    if (memory == nullptr) {
        throw VoleException("Memory not attached to CPU!");
    }

    return *memory;
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
        faultMessage = "Invalid Program Counter address: Must be even and between 00 and FE";

        throw InvalidAddressException(faultMessage);
    }

    programCounter = address;
}

RawInstruction CPU::fetch() {
    if (memory == nullptr) {
        throw VoleException("Memory not attached to CPU!");
    }

    if (programCounter < 0 || programCounter > 0xFE ||
        programCounter % 2 != 0) {

        status = CpuStatus::INVALID_PC;
        faultMessage = "Invalid PC during fetch phase";

        throw InvalidAddressException(faultMessage);
    }

    int highByte = memory->read(programCounter);
    int lowByte = memory->read(programCounter + 1);

    int rawWord = (highByte << 8) | lowByte;

    programCounter += 2;

    return RawInstruction(rawWord);
}

CpuStatus CPU::step() {
    if (status == CpuStatus::HALTED ||
        status == CpuStatus::INVALID_INSTRUCTION ||
        status == CpuStatus::INVALID_PC) {
        return status;
    }

    try {
        if (registers == nullptr || memory == nullptr) {
            throw VoleException("CPU hardware is not attached!");
        }

        instructionRegister = fetch();

        std::unique_ptr<Instruction> instruction =
            decoder.decode(instructionRegister);

        if (instruction == nullptr) {
            throw InvalidInstructionException("Invalid instruction!");
        }

        instruction->execute(*this);

        if (status != CpuStatus::HALTED) {
            status = CpuStatus::READY;
        }
    }
    catch (const InvalidAddressException& e) {
        status = CpuStatus::INVALID_PC;
        faultMessage = e.what();
    }
    catch (const InvalidInstructionException& e) {
        status = CpuStatus::INVALID_INSTRUCTION;
        faultMessage = e.what();
    }
    catch (const std::out_of_range& e) {
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