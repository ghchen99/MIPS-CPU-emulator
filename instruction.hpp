#ifndef H_INSTR
#define H_INSTR

#include <instruction.cpp>

struct instruction{
    int opcode;
    int rs;
    int rt;
    int rd;
    int shamt;
    int funct;
    int imm;
    int address;
    instruction(uint32_t word);    
};

#endif
