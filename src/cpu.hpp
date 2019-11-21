#ifndef H_CPU
#define H_CPU

#include <string>
#include <cstdint>
#include <vector>
#include <exception>

#include "instruction.hpp"

struct memoryException : public std::exception{
    memoryException(const char *msg) : message(msg) {}
    const char *what() const noexcept{ 
        return this->message; 
    }
    const char *message;
};

struct arithmeticException : public std::exception{
    arithmeticException(const char *msg) : message(msg){}
    const char *what() const noexcept{
        return this->message; 
    }
    const char *message;
};

struct instructionException : public std::exception{
    instructionException(const char *msg) : message(msg){}
    const char *what() const noexcept{ 
        return this->message; 
    }
    const char *message;
};

class endException : public std::exception {};

class CPU{
    private:
        std::vector <uint8_t> rom = std::vector <uint8_t> (0x1000000); //read only
        std::vector <uint8_t> ram = std::vector <uint8_t> (0x4000000); //read or write no exectue
        std::vector <uint32_t> r = std::vector <uint32_t> (32);
        std::vector <unsigned int> memoryFlags = std::vector <unsigned int>(5);
        unsigned int instructionFlag;
        uint32_t PC;
        uint32_t hi;
        uint32_t lo;
        instruction currentInstr;
        instruction nextInstr;
        instruction delayInstr;
        
    public:
        CPU();
        void loadRom(uint8_t c, int count);
        void run();
        void reset();
        void next();
        uint32_t addressMap(uint32_t location);
        uint32_t loadInstruction(uint32_t memLocation);
        uint32_t signExtender(uint8_t myNum);
        uint32_t signExtender(uint16_t myNum);
        uint32_t shiftExtender(uint32_t myNum);
        int signReg(int myRegister);
};


#endif
