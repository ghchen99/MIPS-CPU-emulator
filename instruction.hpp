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


enum struct Op unsigned int{
    rType = 0x00;
    
    MFC0 = 0x10;
    
    SLTI = 0x0A;
    SLTIU = 0x0B;
    ANDI = 0x0C;
    ORI = 0x0D;
    LUI = 0x0F;
    SW = 0x2B;
    BEQ = 0x04;
    BNE = 0x05;
    BLEZ = 0x06;
    BGTZ = 0x07;
    ADDI = 0x08;
    ADDIU = 0x09;
    LB = 0x20;
    LW = 0x23;
    LBU = 0x24;
    LHU = 0x25;
    SB = 0x28;
    SH = 0x29;
    
    J = 0x02;
    JAL = 0x03;
};
    

enum struct Fun unsigned int{
    ADD = 0x20;
    ADDU = 0x21;
    AND = 0x24;
    DIV = 0x1A;
    DIVU = 0x1B;
    JR = 0x08;
    MFHI = 0x10;
    MTHI = 0x11;
    MFLO = 0x12;
    MTLO = 0x13;
    MULT = 0x18;
    MULTU = 0x19;
    NOR = 0x27;
    XOR = 0x26;
    OR = 0x25;
    SLT = 0x2A;
    SLTU = 0x2B;
    SLL = 0x00;
    SRL = 0x02;
    SRA = 0x03;
    SUB = 0x22;
    SUBU = 0x23;
};
#endif
