#ifndef H_INSTR
#define H_INSTR

#include <cstdint>

struct instruction{
    int opcode;
    int rs;
    int rt;
    int rd;
    int shamt;
    int funct;
    int imm;
    int address;
    instruction();
    instruction(uint32_t encodedInstruction);    
};

#endif
