#ifndef RAW_INSTRUCTION_H
#define RAW_INSTRUCTION_H

#include <string>
#include <sstream>
#include <iomanip>

class RawInstruction {
private:
    int word;

public:
    RawInstruction(int rawWord = 0) : word(rawWord & 0xFFFF) {}

    int getWord() const { return word; }
    
    int getOpcode() const { return (word >> 12) & 0x0F; }

    int getNibble(int pos) const {
        switch (pos) {
            case 1: return (word >> 12) & 0x0F;
            case 2: return (word >> 8) & 0x0F;
            case 3: return (word >> 4) & 0x0F;
            case 4: return word & 0x0F;
            default: return 0;
        }
    }

    int getLowByte() const { return word & 0xFF; }

    std::string toHex() const {
        std::stringstream ss;
        ss << std::uppercase << std::hex << std::setfill('0') << std::setw(4) << word;
        return ss.str();
    }
};

#endif