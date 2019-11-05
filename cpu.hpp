#ifndef H_CPU
#define H_CPU

#include <string>
#include <cpu.cpp>

class memoryException : public std::exception{
    memoryException(const char *msg) : message(msg) {}
    const char *what() const{ 
        return this->message; 
    }
    const char *msg;
};

class arithmeticException : public std::exception{
    arithmeticException(const char *msg) : message(msg){}
    const char *what() const{
        return this->message; 
    }
    const char *msg;
};
class instructionException : public std::exception{
    instructionException(const char *msg) : message(msg){}
    const char *what() const{ 
        return this->message; 
    }
    const char *msg;
};


class CPU{
    private:
        std::vector <uint8_t> rom(0x1000000);
        std::vector <uint8_t> ram(0x4000000); 
        std::vector <uint32_t> r(32);
        uint32_t PC;
        uint32_t hi;
        uint32_t lo;
        instruction currentInstr;
        instruction nextInstr;
        
    public:
        void setup();
        void reset();
        void next();
        uint32_t AddressMap(uint32_t const &location) const;
        uint32_t loadInstruction(uint32_t const memLocation) const;
}


#endif
