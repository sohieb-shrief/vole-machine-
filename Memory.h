
#ifndef MEMORY_H
#define MEMORY_H

#include <array>
#include <cstdint>
#include "Screen.h"

class Memory {
private:
    std::array<std::uint8_t, 256> cells;
    Screen* screen;

    void validateAddress(int address) const;

public:
    Memory();

    void attachScreen(Screen& screenRef);

    std::uint8_t read(int address) const;
    void write(int address, std::uint8_t value);

    std::uint16_t readWord(int address) const;
    void writeWord(int address, std::uint16_t value);

    bool checkBlock(int startAddress, int length) const;

    void clear();
};

#endif
