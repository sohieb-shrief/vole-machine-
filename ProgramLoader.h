#ifndef PROGRAM_LOADER_H
#define PROGRAM_LOADER_H

#include <string>
#include <vector>
#include "RawInstruction.h"

class ProgramLoader {
public:
    std::vector<RawInstruction> load(const std::string& file);
};

#endif
