
#include "Screen.h"
#include <sstream>
#include <iomanip>

Screen::Screen() {
    clear();
}

void Screen::write(std::uint8_t value) {
    outputValues.push_back(value);
}

std::string Screen::getText() const {
    std::ostringstream output;

    for (std::size_t i = 0; i < outputValues.size(); ++i) {
        if (i > 0) {
            output << " ";
        }

        output << std::uppercase
               << std::hex
               << std::setw(2)
               << std::setfill('0')
               << static_cast<int>(outputValues[i]);
    }

    return output.str();
}

void Screen::clear() {
    outputValues.clear();
}
