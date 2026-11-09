
#ifndef CPU_STATUS_H
#define CPU_STATUS_H

enum class CpuStatus {
    READY,
    HALTED,
    INVALID_INSTRUCTION,
    INVALID_PC
};

#endif
