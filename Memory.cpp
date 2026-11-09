
#include "Memory.h"
#include <stdexcept>

Memory::Memory() : screen(nullptr) {
    clear();
}

void Memory::attachScreen(Screen& screenRef) {
    screen = &screenRef;
}

void Memory::validateAddress(int address) const {
    if (address < 0 || address >= 256) {
        throw std::out_of_range("Memory address must be between 00 and FF");
    }
}

std::uint8_t Memory::read(int address) const {
    validateAddress(address);
    return cells[address];
}

void Memory::write(int address, std::uint8_t value) {
    validateAddress(address);

    cells[address] = value;

    if (address == 0xFF) {
        if (screen == nullptr) {
            throw std::logic_error("Screen is not attached to Memory");
        }

        screen->write(value);
    }
}

std::uint16_t Memory::readWord(int address) const {
    validateAddress(address);

    if (address >= 255) {
        throw std::out_of_range("Cannot read two bytes from this address");
    }

    std::uint16_t high = cells[address];
    std::uint16_t low = cells[address + 1];

    return (high << 8) | low;
}

void Memory::writeWord(int address, std::uint16_t value) {
    validateAddress(address);

    if (address >= 255) {
        throw std::out_of_range("Cannot write two bytes from this address");
    }

    cells[address] = static_cast<std::uint8_t>(value >> 8);
    cells[address + 1] = static_cast<std::uint8_t>(value & 0xFF);

    if (address == 0xFF || address + 1 == 0xFF) {
        throw std::out_of_range("Word write cannot include screen address FF");
    }
}

bool Memory::checkBlock(int startAddress, int length) const {
    if (startAddress < 0 || startAddress >= 256 || length < 0) {
        return false;
    }

    return startAddress + length <= 256;
}

void Memory::clear() {
    cells.fill(0);

    if (screen != nullptr) {
        screen->clear();
    }
}
