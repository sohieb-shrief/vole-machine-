
#ifndef SCREEN_H
#define SCREEN_H

#include <vector>
#include <cstdint>
#include <string>

class Screen {
private:
    std::vector<std::uint8_t> outputValues;

public:
    Screen();

    void write(std::uint8_t value);
    std::string getText() const;
    void clear();
};

#endif
