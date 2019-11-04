#include <string>
#include <cpu.hpp>


void run(){
//call next until end or an exception is found
    try{
        for(int i = 0; /*i < bin.size(); i+= 32*/){
        }
    }
    catch(){
    }
        
}
void reset(){
//set all registers to 0, set PC = 0x
    for(int i = 0; i<r.size(); i++){
        r[i] = 0;
    }
    PC = 0x10000000;
}
void next(){
//increment PC, read/start next instruction
    switch (instruction.opcode) {
      //rType
      case 0x00:
        switch (instruction.funct) {
          //ADD
          case 0x20{
            if(((r[instruction.rs] >> 31) == 1) && ((r[instruction.rs] >> 31) == 0)){
              r[instruction.rd] = ~r[instruction.rs] + 1 + r[instruction.rs];
            }
            else if(((r[instruction.rs] >> 31) == 0) && ((r[instruction.rs] >> 31) == 1)){
              r[instruction.rd] = r[instruction.rs] + ~r[instruction.rs] + 1;
            }
            else if(((r[instruction.rs] >> 31) == 1) && ((r[instruction.rs] >> 31) == 1)){
              r[instruction.rd] = ~r[instruction.rs] + ~r[instruction.rs] + 2;
            }
            else{
              r[instruction.rd] = r[instruction.rs] + r[instruction.rt];
            }
            break;
          }
          //ADDU
          case 0x21{
            r[instruction.rd] = r[instruction.rs] + r[instruction.rt];
            break;
          }
          //AND
          case 0x24{
            r[instruction.rd] = r[instruction.rs] && r[instruction.rt];
            break;
          }
          //DIV
          case 0x1A{
            std::cout << "DIV" << '\n';
            if(((r[instruction.rs] && 0x80000000) == 1) && ((r[instruction.rs] && 0x80000000) == 0)){
                std::cout << "UNSIGNED OH NO";
            }
            else{
                r[instruction.rd] = r[instruction.rs] / r[instruction.rt];
            }
            break;
          }
          //DIVU
          case 0x1B{
            std::cout << "DIVU" << '\n';
            r[instruction.rd] = r[instruction.rs] / r[instruction.rt];
            break;
          }
          //JR
          case 0x08{
            std::cout << "JR" << '\n';
            break;
          }
          //MFHI
          case 0x10{
            std::cout << "MFHI" << '\n';
            break;
          }
          //MTHI
          case 0x11{
            std::cout << "MTHI" << '\n';
            break;
          }
          //MFLO
          case 0x12{
            std::cout << "MFLO" << '\n';
            break;
          }
          //MTLO
          case 0x13{
            std::cout << "MTLO" << '\n';
            break;
          }
          //MULT
          case 0x18{
            std::cout << "MULT" << '\n';
            break;
          }
          //MULTU
          case 0x19{
            std::cout << "MULTU" << '\n';
            break;
          }
          //NOR
          case 0x27{
            std::cout << "NOR" << '\n';
            break;
          }
          //XOR
          case 0x26{
            std::cout << "XOR" << '\n';
            break;
          }
          //OR
          case 0x25{
            std::cout << "OR" << '\n';
            break;
          }
          //SLT
          case 0x2A{
            std::cout << "SLT" << '\n';
            break;
          }
          //SLTU
          case 0x2B{
            std::cout << "SLTU" << '\n';
            break;
          }
          //SLL
          case 0x00{
            std::cout << "SLL" << '\n';
            break;
          }
          //SRL
          case 0x02{
            std::cout << "SRL" << '\n';
            break;
          }
          //SRA
          case 0x03{
            std::cout << "SRA" << '\n';
            break;
          }
          //SUB
          case 0x22{
            std::cout << "SUB" << '\n';
            break;
          }
          //SUBU
          case 0x23{
            std::cout << "SUBU" << '\n';
            break;
          }
        }
        //MFC0
        case 0x10{
          std::cout << "MFC0" << '\n';
          break;
        }
        //SLTI
        case 0x0A{
          std::cout << "SLTI" << '\n';
          break;
        }
        //SLITU
        case 0x0B{
          std::cout << "SLITU" << '\n';
          break;
        }
        //ANDI
        case 0x0C{
          std::cout << "ANDI" << '\n';
          break;
        }
        //ORI
        case 0x0D{
          std::cout << "ORI" << '\n';
          break;
        }
        //LUI
        case 0x0F{
          std::cout << "LUI" << '\n';
          break;
        }
        //SW
        case 0x2B{
          std::cout << "SW" << '\n';
          break;
        }
        //BEQ
        case 0x04{
          std::cout << "BEQ" << '\n';
          break;
        }
        //BNE
        case 0x05{
          std::cout << "BNE" << '\n';
          break;
        }
        //BLEZ
        case 0x06{
          std::cout << "BLEZ" << '\n';
          break;
        }
        //BGTZ
        case 0x07{
          std::cout << "BGTZ" << '\n';
        }
        //ADDI
        case 0x08{

        }
        //ADDIU
        case 0x09{

        }
        //LB
        case 0x20{

        }
        //LW
        case 0x23{

        }
        //LBU
        case 0x24{

        }
        //LHU
        case 0x25{

        }
        //SB
        case 0x28{

        }
        //SH
        case 0x29{

        }
        //J
        case 0x02{

        }
        //JAL
        case 0x03{

        }
        // Missing BGEZ, BGEZAL, BLEZAL, JALR, LH, LWL, LWR
        // SLLV, SRAV, XORI
    }

    PC += 4;
    
}
void AddressMap(){
//check validity of address for read/write, alter the offsets, and give exceptions
    if(0x10000000 < location < 0x11000000){
        location -= 0x10000000;
    }
    if(0x20000000 < location < 0x24000000){
        location -= 0x2000000;
    }
    if(0x3000000 < location < 0x3000004){
//do something
    }
    if(0x3000004 < location < 0x3000008){
//do something
    }
    if(0x0000000 < location < 0x4){
//do something
    }
    else{
        throw MemoryException
    }
}
