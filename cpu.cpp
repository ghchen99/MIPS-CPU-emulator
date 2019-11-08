#include <string>
#include <cstdint>
#include <vector>
#include <iostream>

#include "cpu.hpp"
#include "instruction.hpp"

CPU::CPU(){
    memoryFlags[0] = 0b001; //ADDR_NULL - execute
    memoryFlags[1] = 0b101; //ADDR_INSTR - read, execute
    memoryFlags[2] = 0b110; //ADDR_DATA - read, write
    memoryFlags[3] = 0b100; //ADDR_GETC - read
    memoryFlags[4] = 0b010; //ADDR_PUTC - write
    std::fill(ram.begin(), ram.end(), 0x00);
    std::fill(rom.begin(), rom.end(), 0x00);
    std::fill(r.begin(), r.end(), 0x00000000);
}

void CPU::loadRom(uint8_t c, int count){
    rom[count] = c;
}

void CPU::run(){
//call next until end or an exception is found
    try{
        for(int i = 0; i < /*bin.size()*/ 0x1000000; i+= 32){
            this->next();
        }
    }
    catch(endException&){
    }
        
}
void CPU::reset(){
//set all registers to 0, set PC = 0x
    std::fill(r.begin(), r.end(), 0x00000000);
    PC = 0x10000000;
}

//increment PC, compute current instruction, read next instruction
void CPU::next(){
    //getting next instruction
    currentInstr = nextInstr;
    try{
        instruction nextInstr(loadInstruction(PC));
    }
    catch(memoryException){
        //something
    }
    catch(instructionException){
        //something
    }
    
    PC += 4;
        
    //doing instruction; for load instructions do no operation
        
    switch(currentInstr.opcode) {

      //rType
    case 0x00:
        {
            switch (currentInstr.funct) {
                
            //ADD
                case 0x20:
                {
                    currentInstr.rs = 80;
                    currentInstr.rt = 80;
                    if(((r[currentInstr.rs] >> 31) == 1) && ((r[currentInstr.rt] >> 31) == 0)){
                        r[currentInstr.rd] = ~r[currentInstr.rs] + 1 + r[currentInstr.rt];
                    }
                    else if(((r[currentInstr.rs] >> 31) == 0) && ((r[currentInstr.rt] >> 31) == 1)){
                        r[currentInstr.rd] = r[currentInstr.rs] + ~r[currentInstr.rt] + 1;
                    }
                    else if(((r[currentInstr.rs] >> 31) == 1) && ((r[currentInstr.rt] >> 31) == 1)){
                        r[currentInstr.rd] = ~r[currentInstr.rs] + ~r[currentInstr.rt] + 2;
                    }
                    else{
                        r[currentInstr.rd] = r[currentInstr.rs] + r[currentInstr.rt];
                    }
                    std::cout << r[currentInstr.rd] << std::endl;
                    break;
                }
            
            //ADDU
                case 0x21:
                {
                    r[currentInstr.rd] = r[currentInstr.rs] + r[currentInstr.rt];
//                     if(((r[currentInstr.rs] >> 31) == 1) && ((r[currentInstr.rt] >> 31) == 1) && ((r[currentInstr.rd] >> 31) == 0)){
//                         throw arithmeticException("Unsigned overflow");
//                     }
                    break;
                }

            //AND
                case 0x24:
                {
                    r[currentInstr.rd] = r[currentInstr.rs] & r[currentInstr.rt];
                    break;
                }

            //DIV
                case 0x1A:
                {
                    if(currentInstr.rt == 0){
                        throw arithmeticException("Tried to divide by 0");
                    }
                    //hi = static_cast<uint32_t>(sr[currentInstr.rs] % sr[currentInstr.rt]);
                    //lo = static_cast<uint32_t>(sr[currentInstr.rs] / sr[currentInstr.rt]);
                break;
                }

            //DIVU
                case 0x1B:
                {
                    if(currentInstr.rt == 0){
                        throw arithmeticException("Tried to divide by 0");
                    }
                    hi = r[currentInstr.rs] % r[currentInstr.rt];
                    lo = r[currentInstr.rs] / r[currentInstr.rt];
                    break;
                }

            //JR
                case 0x08:
                {
                    PC = r[currentInstr.rs];
                    break;
                }

            //MFHI
                case 0x10:
                {
                    r[currentInstr.rd] = hi;
                    break;
                }

            //MTHI
                case 0x11:
                {
                    hi = r[currentInstr.rs];
                    break;
                }
                
            //MFLO
                case 0x12:
                {
                    r[currentInstr.rd] = lo;
                    break;
                }

            //MTLO
                case 0x13:
                {
                    lo = r[currentInstr.rs];
                    break;
                }

            //MULT
                case 0x18:
                {
                    uint64_t product = r[currentInstr.rs] * r[currentInstr.rt];
                    hi = static_cast<uint64_t> (product >> 32);
                    lo = static_cast<uint64_t> (product & 0xffffffff);
                    break;
                }

            //MULTU
                case 0x19:
                {
                    uint64_t product = r[currentInstr.rs] * r[currentInstr.rt];
                    hi = product >> 32;
                    lo = product & 0xffffffff;
                    break;
                }
            
            //NOR
                case 0x27:
                {
                    r[currentInstr.rd] = ~(r[currentInstr.rs] | r[currentInstr.rt]);
                    break;
                }
                
            //XOR
                case 0x26:
                {
                    r[currentInstr.rd] = r[currentInstr.rs] ^ r[currentInstr.rt];
                    break;
                }
            
            //OR
                case 0x25:
                {
                    r[currentInstr.rd] = r[currentInstr.rs] | r[currentInstr.rt];
                    break;
                }
            
            //SLT
                case 0x2A:
                {
                    //r[currentInstr.rd] = sr[currentInstr.rs] < sr[currentInstr.rt];
                    break;
                }
            
            //SLTU
                case 0x2B:
                {
                    //r[currentInstr.rd] = r[currentInstr.rs] < sr[currentInstr.rt];
                    break;
                }
            
            //SLL
                case 0x00:
                {
                    r[currentInstr.rd] = r[currentInstr.rt] << currentInstr.shamt;
                    break;
                }
            
            //SRL
                case 0x02:
                {
                    r[currentInstr.rd] = r[currentInstr.rt] >> currentInstr.shamt;
                    break;
                }
            
            //SRA
                case 0x03:
                {
                    //sr[currentInstr.rd] = sr[currentInstr.rt] >> currentInstr.shamt;
                    break;
                }
            
            //SUB
                case 0x22:
                {
                    if(((r[currentInstr.rs] >> 31) == 1) && ((r[currentInstr.rs] >> 31) == 0)){
                        r[currentInstr.rd] = ~r[currentInstr.rs] + 1 - r[currentInstr.rs];
                    }
                    else if(((r[currentInstr.rs] >> 31) == 0) && ((r[currentInstr.rs] >> 31) == 1)){
                        r[currentInstr.rd] = r[currentInstr.rs] - (~r[currentInstr.rs] + 1);
                    }
                    else if(((r[currentInstr.rs] >> 31) == 1) && ((r[currentInstr.rs] >> 31) == 1)){
                        r[currentInstr.rd] = ~r[currentInstr.rs] - ~r[currentInstr.rs];
                    }
                    else{
                        r[currentInstr.rd] = r[currentInstr.rs] - r[currentInstr.rt];
                    }
                    break;
                }
            
                //SUBU
                case 0x23:
                {
                    r[currentInstr.rd] = r[currentInstr.rs] - r[currentInstr.rt];
                    break;
                }
            }
        }
    //MFC0
    case 0x10:
    {
        std::cout << "MFC0" << '\n';
        break;
    }
    
    //SLTI
    case 0x0A:
    {
        std::cout << "SLTI" << '\n';
        break;
    }
    
    //SLITU
    case 0x0B:
    {
        std::cout << "SLITU" << '\n';
        break;
    }
    
    //ANDI
    case 0x0C:
    {
        std::cout << "ANDI" << '\n';
        break;
    }
    
    //ORI
    case 0x0D:
    {
        std::cout << "ORI" << '\n';
        break;
    }
    
    //LUI
    case 0x0F:
    {
        std::cout << "LUI" << '\n';
        break;
    }
    
    //SW
    case 0x2B:
    {
        std::cout << "SW" << '\n';
        break;
    }
    
    //BEQ
    case 0x04:
    {
        std::cout << "BEQ" << '\n';
        break;
    }
    
    //BNE
    case 0x05:
    {
        std::cout << "BNE" << '\n';
        break;
    }
    
    //BLEZ
    case 0x06:
    {
        std::cout << "BLEZ" << '\n';
        break;
    }
    
    //BGTZ
    case 0x07:
    {
        std::cout << "BGTZ" << '\n';
        break;
    }
    
    //ADDI
    case 0x08:
    {
        
    }

    
    //ADDIU
    case 0x09:
    {
        
    }

    
    //LB
    case 0x20:
    {
        
    }

    
    //LW
    case 0x23:
    {
        
    }

    
    //LBU
    case 0x24:
    {
        
    }

    
    //LHU
    case 0x25:
    {
        
    }

    
    //SB
    case 0x28:
    {
        
    }

    
    //SH
    case 0x29:
    {
        
    }

    
    //J
    case 0x02:
    {
        
    }

    
    //JAL
    case 0x03:
    {
        
    }

        
        // Missing BGEZ, BGEZAL, BLEZAL, JALR, LH, LWL, LWR
        // SLLV, SRAV, XORI
    
    }

    
    //do delayed instruction
    switch(delayInstr.opcode){
        //do instructions LB, LH, LW, LBU, LHU here (delayed instructions) and then clear delayInstr
    }
    
    
    r[0] = 0;
    
    //load next delay operation
    switch(currentInstr.opcode){
        //set instructions LB, LH, LW, LBU, LHU to delayInstr here (delayed instructions)
        //LB
        case 0x20:
        //LW
        case 0x23:
        //LBU
        case 0x24:
        //LHU
        case 0x25:
        delayInstr = currentInstr;
        default:
            break;
        
    }
}

uint32_t CPU::addressMap(uint32_t location){
//check validity of address for read/write, alter the offsets, and give exceptions
    if(0x0000000 < location < 0x4){
        if(instructionFlag && memoryFlags[0] == 0b000){
            throw memoryException("Tried to read/write/execute illegally");
        }
//do something
    }
    if(0x10000000 < location < 0x11000000){
        if(instructionFlag && memoryFlags[1] == 0b000){
            throw memoryException("Tried to read/write/execute illegally");
        }
        return location - 0x10000000;
    }
    if(0x20000000 < location < 0x24000000){
        if(instructionFlag && memoryFlags[2] == 0b000){
            throw memoryException("Tried to read/write/execute illegally");
        }
        return location - 0x20000000;
    }
    if(0x3000000 < location < 0x3000004){
        if(instructionFlag && memoryFlags[3] == 0b000){
            throw memoryException("Tried to read/write/execute illegally");
        }
//do something
    }
    if(0x3000004 < location < 0x3000008){
        if(instructionFlag && memoryFlags[4] == 0b000){
            throw memoryException("Tried to read/write/execute illegally");
        }
//do something
    }
    else{
        throw memoryException("Tried to access invalid memory address");
    }
}

uint32_t CPU::loadInstruction(uint32_t memLocation){
    instructionFlag = 0b100;
    uint32_t mappedLocation = addressMap(memLocation);
    return (rom[mappedLocation] << 24) || (rom[mappedLocation + 1] << 16) || (rom[mappedLocation + 2] << 8) || (rom[mappedLocation + 3]);
}
