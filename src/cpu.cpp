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
    //try{
        for(int i = 0; i < /*bin.size()*/ 0x1000000; i+= 4){
            this->next();
        }
    //}
    /*catch(endException& e){
        std::cerr << "unexpected termination: ";
        std::cerr << e.what() << std::endl;
    }*/
        
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
    if(PC & 0x03 != 0){
        //throw endException(); //misaligned PC
        std::exit(-11);
    }
    //try{
        instruction nextInstr(loadInstruction(PC));
    //}
    /*catch(memoryException& e){
        std::cerr << "memory exception: ";
        std::cerr << e.what() << std::endl;
    }
    catch(instructionException& e){
        std::cerr << "instruction exception ";
        std::cerr << e.what() << std::endl;
    }*/
    
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
                    int sum, LHS, RHS;
                    LHS = signReg(currentInstr.rs);
                    RHS = signReg(currentInstr.rt);
                    
                    if(((LHS >= 0 && RHS >= 0) && (0x7FFFFFFF - LHS <= RHS))
                        || ((LHS < 0 && RHS < 0) && (LHS <= 0x80000000 - RHS))){
                        //throw arithmeticException("signed overflow");
                        std::exit(-10);
                    }
                    else{
                        r[currentInstr.rd] = sum & 0xffffffff;
                    }
                    break;
                }
            
            //ADDU
                case 0x21:
                {
                    uint64_t sum;
                     sum = r[currentInstr.rs] + r[currentInstr.rt];
                     if(sum >> 32 >= 0){
                         //throw arithmeticException("Unsigned overflow");
                         std::exit(-10);
                     }
                     break;
                }

            //AND
                case 0x24:
                {
                    r[currentInstr.rd] = r[currentInstr.rs] & r[currentInstr.rt];
                    break;
                }

            //DIV - NEEDS FINISHING
                case 0x1A:
                {
                    
                    if(currentInstr.rt == 0){
                        //throw arithmeticException("Tried to divide by 0");
                        std::exit(-10);
                    }
                        hi = static_cast<uint32_t> (signReg(currentInstr.rs) % signReg(currentInstr.rt));
                        lo = static_cast<uint32_t> (signReg(currentInstr.rs) / signReg(currentInstr.rt));
                    }
                break;
                }

            //DIVU
                case 0x1B:
                {
                    if(currentInstr.rt == 0){
                        //throw arithmeticException("Tried to divide by 0");
                        std::exit(-10);
                    }
                    hi = r[currentInstr.rs] % r[currentInstr.rt];
                    lo = r[currentInstr.rs] / r[currentInstr.rt];
                    break;
                }
            //JALR
                case 0x09:
                {
                    r[currentInstr.rd] = PC;
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
                    int64_t product = signReg(currentInstr.rs) * signReg(currentInstr.rt);
                    hi = static_cast<uint32_t> (product >> 32);
                    lo = static_cast<uint32_t> (product & 0xffffffff);
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
                    if(((r[currentInstr.rs] >> 31) == 1) && ((r[currentInstr.rt] >> 31) == 0)){
                        r[currentInstr.rd] = ~r[currentInstr.rs] + 1 < r[currentInstr.rt];
                    }
                    else if(((r[currentInstr.rs] >> 31) == 0) && ((r[currentInstr.rt] >> 31) == 1)){
                        r[currentInstr.rd] = r[currentInstr.rs] < - (~r[currentInstr.rt] + 1);
                    }
                    else if(((r[currentInstr.rs] >> 31) == 1) && ((r[currentInstr.rt] >> 31) == 1)){
                        r[currentInstr.rd] = ~r[currentInstr.rs] < ~r[currentInstr.rt];
                    }
                    else{
                        r[currentInstr.rd] = r[currentInstr.rs] < r[currentInstr.rt];
                    }
                    break;
                }
            
            //SLTU
                case 0x2B:
                {
                    r[currentInstr.rd] = r[currentInstr.rs] < r[currentInstr.rt];
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
                    uint32_t myNum = r[currentInstr.rt] >> currentInstr.shamt;
                    r[currentInstr.rd] = shiftExtender(myNum);                      
                    break;
                }
            //SRAV
                case 0x07:
                {
                    uint32_t myNum = r[currentInstr.rt] >> r[currentInstr.rs];
                    r[currentInstr.rd] = shiftExtender(myNum); 
                    break;
                }
            //SLLV
                case 0x04:
                {
                    r[currentInstr.rd] = r[currentInstr.rt] << r[currentInstr.rs];
                    break;
                }
            //SRLV
                case 0x06:
                {
                    r[currentInstr.rd] = r[currentInstr.rt] >> r[currentInstr.rs];
                }
            
            //SUB
                case 0x22:
                {
                    if(((r[currentInstr.rs] >> 31) == 1) && ((r[currentInstr.rt] >> 31) == 0)){
                        r[currentInstr.rd] = -(~r[currentInstr.rs] + 1) - r[currentInstr.rt];
                    }
                    else if(((r[currentInstr.rs] >> 31) == 0) && ((r[currentInstr.rt] >> 31) == 1)){
                        r[currentInstr.rd] = r[currentInstr.rs] + ~r[currentInstr.rt] + 1;
                    }
                    else if(((r[currentInstr.rs] >> 31) == 1) && ((r[currentInstr.rt] >> 31) == 1)){
                        r[currentInstr.rd] = -(~r[currentInstr.rs]) + ~r[currentInstr.rt];
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
                default:
                    //throw instructionException("Invalid function code");
                    std::exit(-12);
            }
        }
    
    //SLTI
    case 0x0A:
    {
        if(r[currentInstr.rs] & 0x80000000 == 0){
            if(r[currentInstr.rs] < currentInstr.simm){
                r[currentInstr.rt] = 1;
            }
            else{
              r[currentInstr.rt] = 0;
            }
        }
        else{
            if(r[currentInstr.rs] < currentInstr.simm){
                r[currentInstr.rt] = 1;
            }
            else{
              
            }
        }
        break;
    }
    
    //SLITU
    case 0x0B:
    {
        r[currentInstr.rt] = r[currentInstr.rs] < currentInstr.simm;
        break;
    }
    
    //ANDI
    case 0x0C:
    {
        r[currentInstr.rt] = r[currentInstr.rs] & currentInstr.simm;
        break;
    }
    
    //ORI
    case 0x0D:
    {
        r[currentInstr.rt] = r[currentInstr.rs] | currentInstr.imm;
        break;
    }
    
    //XORI
    case 0x0E:
    {
        r[currentInstr.rt] = r[currentInstr.rs] ^ currentInstr.imm;
        break;   
    }
    //LUI
    case 0x0F:
    {
        r[currentInstr.rt] = currentInstr.imm << 16;
        break;
    }
    
    //SW
    case 0x2B:
    {
        if(r[currentInstr.rs] + currentInstr.simm << 30 != 0){
            //throw memoryException("Address error, misaligned address");
            std::exit(-11);
        }
        instructionFlag = 0b100;
        uint32_t mappedLocation = addressMap(r[currentInstr.rs] + currentInstr.simm);
        uint8_t b0 = r[currentInstr.rt] & 0xff;
        uint8_t b1 = (r[currentInstr.rt] >> 8) & 0xff;
        uint8_t b2 = (r[currentInstr.rt] >> 16) & 0xff;
        uint8_t b3 = r[currentInstr.rt] >> 24;
        ram[mappedLocation] = b3;
        ram[mappedLocation + 1] = b2;
        ram[mappedLocation + 2] = b1;
        ram[mappedLocation + 3] = b0;
        break;
    }
    
    //BEQ
    case 0x04:
    {
        if(r[currentInstr.rs] == r[currentInstr.rt]){
            PC += (static_cast<int32_t>(currentInstr.imm) << 2) - 4;        
        }
        break;
    }
    
    //BNE
    case 0x05:
    {
        if(r[currentInstr.rs] != r[currentInstr.rt]){
            PC += (static_cast<int32_t>(currentInstr.imm) << 2) - 4;        
        }
        break;
    }
    
    //BLEZ
    case 0x06:
    {
        if(r[currentInstr.rs] <= 0){
            PC += (static_cast<int32_t>(currentInstr.imm) << 2) - 4;        
        }
        break;
    }
    
    //BGTZ
    case 0x07:
    {
        if(r[currentInstr.rs] > 0){
            PC += (static_cast<int32_t>(currentInstr.imm) << 2) - 4;        
        }
        break;
    }
    
    //BGEZ, BGEZAL, BLTZAL, BLTZ
    case 0x01:
        switch(currentInstr.rt){
            //BGEZAL
            case 0x11:
            {
                r[31] = PC;
            }
            //BGEZ
            case 0x01:
            {
                if(currentInstr.rs >= 0){
                    uint32_t offset = currentInstr.imm * 4;
                    PC += offset - 4;
                }
                break;
            }
            //BLTZAL
            case 0x10:
            {
                r[31] = PC;
            }
            //BLTZ
            case 0x00:
            {
                if(currentInstr.rs < 0){
                    uint32_t offset = currentInstr.imm * 4;
                    PC += offset - 4;
                }
                break;
            }
            default:
                //throw instructionException("Invalid branch code");
                std::exit(-12);
        }
    
    //ADDI overflow error add here
    
    case 0x08:
    {
        uint64_t sum;
        sum = r[currentInstr.rs] + currentInstr.simm;
        break;
    }

    
    //ADDIU
    case 0x09:
    {
        r[currentInstr.rt] = r[currentInstr.rs] + currentInstr.simm;
        break;
    }

    
    //LB
    case 0x20:
    {
        break;
    }

    
    //LW
    case 0x23:
    {
        break;
    }

    
    //LBU
    case 0x24:
    {;
        break;
    }

    
    //LHU
    case 0x25:
    {
        break;
    }

    
    //SB
    case 0x28:
    {
        instructionFlag = 0b100;
        uint32_t mappedLocation = addressMap(r[currentInstr.rs] + currentInstr.simm);
        uint8_t b0 = r[currentInstr.rt] & 0xff;
        ram[mappedLocation] = b0;
        break;
    }

    
    //SH
    case 0x29:
    {
        if(r[currentInstr.rs] + currentInstr.simm){

        }
        instructionFlag = 0b100;
        uint32_t mappedLocation = addressMap(r[currentInstr.rs] + currentInstr.simm);
        uint8_t b0 = r[currentInstr.rt] & 0xff;
        uint8_t b1 = r[currentInstr.rt] >> 8;
        ram[mappedLocation] = b1;
        ram[mappedLocation + 1] = b0;
        break;
    }

    
    //J
    case 0x02:
    {
        PC = (PC & 0xf0000000) | (currentInstr.address << 2);
    }

    
    //JAL
    case 0x03:
    {
        r[31] = PC;
        break;
    }
    
    //LH
    case 0x21:    
    {
        break;
    }
    
    default:
        //throw instructionException("Invalid opcode");
        std::exit(-12);
    }

    
    //do delayed instruction
    switch(delayInstr.opcode){
        //do instructions LB, LH, LW, LBU, LHU here (delayed instructions) and then clear delayInstr
        //LB
        case 0x20:
        {
            instructionFlag = 0b100;
            uint32_t location = currentInstr.rs + currentInstr.simm;
            uint32_t mappedLocation = addressMap(location);
            if((0x3000000 <= location) && (location <= 0x3000004)){
                char myInput;
                std::cin >> myInput;
                uint32_t extendedInput = signExtender(static_cast<uint8_t> (myInput));
                r[currentInstr.rt] = extendedInput;
            }
            if((0x20000000 <= location) && (location <= 0x24000000)){
                currentInstr.rt = rom[mappedLocation];
            }
            else{
                currentInstr.rt = ram[mappedLocation]; //sign extend this
            }
            delayInstr.opcode = 0xFF; //cannot set int to NULL so setting delayInstr to a value that will never be in switch statement
            break;
        }
        //LW
        case 0x23:
        {
            instructionFlag = 0b100;
            uint32_t location = currentInstr.rs + currentInstr.simm;
            uint32_t mappedLocation = addressMap(location);
            if((0x3000000 <= location) && (location <= 0x3000004)){
                char myInput;
                std::cin >> myInput;
                uint32_t extendedInput = signExtender(static_cast<uint8_t> (myInput));
                r[currentInstr.rt] = extendedInput;
            }
            if((0x20000000 <= location) && (location <= 0x24000000)){
                currentInstr.rt = (rom[mappedLocation] << 24) | (rom[mappedLocation + 1] << 16) | (rom[mappedLocation + 2] << 8) | (rom[mappedLocation + 3]);
            }
            else{
                currentInstr.rt = (ram[mappedLocation] << 24) | (ram[mappedLocation + 1] << 16) | (ram[mappedLocation + 2] << 8) | (ram[mappedLocation + 3]);
            }
            delayInstr.opcode = 0xFF;
            break;
            
        }
        //LBU
        case 0x24:
        {
            instructionFlag = 0b100;
            uint32_t location = currentInstr.rs + currentInstr.simm;
            uint32_t mappedLocation = addressMap(location);
            if((0x3000000 <= location) && (location <= 0x3000004)){
                char myInput;
                std::cin >> myInput;
                uint32_t extendedInput = signExtender(static_cast<uint8_t> (myInput));
                r[currentInstr.rt] = extendedInput;
            }
            if((0x20000000 <= location) && (location <= 0x24000000)){
                currentInstr.rt = rom[mappedLocation];
            }
            else{
                currentInstr.rt = ram[mappedLocation]; //no sign extension
            }
            delayInstr.opcode = 0xFF;
            break;
        }
        //LH
        case 0x21:
        {
            instructionFlag = 0b100;
            uint32_t location = currentInstr.rs + currentInstr.simm;
            uint32_t mappedLocation = addressMap(location);
            if((0x20000000 <= location) && (location <= 0x24000000)){
                currentInstr.rt = (rom[mappedLocation] << 8) | rom[mappedLocation + 1];
            }
            else{
                currentInstr.rt = (ram[mappedLocation] << 8) | ram[mappedLocation + 1]; //no sign extension
            }
            delayInstr.opcode = 0xFF;
            break;
        }
        //LHU
        case 0x25:
        {
            instructionFlag = 0b100;
            uint32_t location = currentInstr.rs + currentInstr.simm;
            uint32_t mappedLocation = addressMap(location);
            if((0x20000000 <= location) && (location <= 0x24000000)){
                currentInstr.rt = (rom[mappedLocation] << 8) | rom[mappedLocation + 1];
            }
            else{
                currentInstr.rt = (ram[mappedLocation] << 8) | ram[mappedLocation + 1]; //no sign extension
            }
            delayInstr.opcode = 0xFF;
            break;
        }
        default:
            break;
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
        //LH
        case 0x21:
        //LHU
        case 0x25:
        delayInstr = currentInstr;
        default:
            break;
        
    }
}

uint32_t CPU::addressMap(uint32_t location){
//check validity of address for read/write, alter the offsets, and give exceptions
    if((0x0000000 <= location) && (location <= 0x4)){
        if(instructionFlag && memoryFlags[0] == 0b000){
            //throw memoryException("Tried to read/write/execute illegally");
            std::exit(-12);
        }
//do something
    }
    if((0x10000000 <= location) && (location <= 0x11000000)){
        if(instructionFlag && memoryFlags[1] == 0b000){
            //throw memoryException("Tried to read/write/execute illegally");
            std::exit(-12);
        }
        return location - 0x10000000;
    }
    if((0x20000000 <= location) && (location <= 0x24000000)){
        if(instructionFlag && memoryFlags[2] == 0b000){
            //throw memoryException("Tried to read/write/execute illegally");
            std::exit(-12);
        }
        return location - 0x20000000;
    }
    if((0x3000000 <= location) && (location <= 0x3000004)){
        if(instructionFlag && memoryFlags[3] == 0b000){
            //throw memoryException("Tried to read/write/execute illegally");
            std::exit(-12);
        }
//do something
    }
    if((0x3000004 <= location) && (location <= 0x3000008)){
        if(instructionFlag && memoryFlags[4] == 0b000){
            //throw memoryException("Tried to read/write/execute illegally");
            std::exit(-12);
        }
//do something
    }
    else{
        //throw memoryException("Tried to access invalid memory address");
        std::exit(-12);
    }
}

uint32_t CPU::loadInstruction(uint32_t memLocation){
    instructionFlag = 0b100;
    uint32_t mappedLocation = addressMap(memLocation);
    return (rom[mappedLocation] << 24) | (rom[mappedLocation + 1] << 16) | (rom[mappedLocation + 2] << 8) | (rom[mappedLocation + 3]);
}

uint32_t CPU::signExtender(uint8_t myNum){
    uint32_t newNum;
    if(myNum & 0x80){
        newNum = myNum | 0xffffff00;
    }
    else{
        newNum = myNum | 0x00000000;
    }
    return newNum;
}

uint32_t CPU::signExtender(uint16_t myNum){
    uint32_t newNum;
    if(myNum & 0x80){
        newNum = myNum | 0xffff0000;
    }
    else{
        newNum = myNum | 0x00000000;
    }
    return newNum;
}

uint32_t CPU::shiftExtender(uint32_t myNum){
    if((r[currentInstr.rt] >> 31) == 1){
        for(int i = 0, j = 31; i < currentInstr.shamt; i++, j--){
            myNum = myNum | (1 << j);
        }
    }
    return myNum;
}

int CPU::signReg(int myRegister){
    if(r[myRegister] >> 31){
        int signedConvert = ~(r[myRegister]) + 1;
        return -signedConvert;
    }
    else{
        return r[myRegister];
    }
}
    
