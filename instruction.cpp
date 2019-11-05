#include "instruction.hpp"
#include <cstdint>

//default constructor

instruction::instruction(){
    this -> opcode = 0;
    this -> rs = 0;
    this -> rt = 0;
    this -> rd = 0;
    this -> shamt = 0;
    this -> funct = 0;
    this -> imm = 0;
    this -> address = 0;
}
//constructor for instruction is decoder
instruction::instruction(uint32_t word){
    this->opcode = (word >> 26);
    if(this->opcode == 0){
        this->rs = (word >> 21) & 0x1f;
        this->rt = (word >> 16) & 0x1f;
        this->rd = (word >> 11) & 0x1f;
        this->shamt = (word >> 6) & 0x1f;
        this->funct = word & 0x3f;
        this->imm = 0;
        this->address = 0;
    }
    else if(this->opcode == 2 || this->opcode == 3){
        this->rs = 0;
        this->rt = 0;
        this->rd = 0;
        this->shamt = 0;
        this->funct = 0;
        this->imm = 0;
        this->address = word & 0x3ffffff;
    }
    else{
        this->rs = (word >> 21) & 0x1f;
        this->rt = (word >> 16) & 0x1f;
        this->rd = 0;
        this->shamt = 0;
        this->funct = 0;
        this->imm = word & 0xffff;
        this->address = 0;
    }
}
