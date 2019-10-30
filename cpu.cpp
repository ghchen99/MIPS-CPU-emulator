#include <string>
#include <cpu.hpp>


void setup(){
#create registers, rom/ram, load bin into rom, set r0 = 0, set PC = entry location
}
void reset(){
#set all registers to 0, set PC = entry location
}
void next(){
#increment PC, read/start next instruction
}
void AddressMapper(){
#check validity of address for read/write, alter the offsets, and give exceptions
}
