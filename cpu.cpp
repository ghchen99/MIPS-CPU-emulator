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
    PC = 0;
}
void next(){
//increment PC, read/start next instruction
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
