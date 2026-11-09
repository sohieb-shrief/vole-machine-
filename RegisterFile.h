#ifndef REGISTER_FILE_H
#define REGISTER_FILE_H

#include <cstdint>
#include <array>
#include <stdexcept>

class RegisterFile {
private:
    std::array<std::uint8_t, 16> values;

public:
    RegisterFile() {
        clear();
    }

    std::uint8_t get(int i) const {
        if (i < 0 || i >= 16) {
            throw std::out_of_range("Register index out of range (0-15 expected)");
        }
        return values[i];
    }

    void set(int i, std::uint8_t v) {
        if (i < 0 || i >= 16) {
            throw std::out_of_range("Register index out of range (0-15 expected)");
        }
        values[i] = v;
    }

    void clear() {
        values.fill(0);
    }
};

#endif 