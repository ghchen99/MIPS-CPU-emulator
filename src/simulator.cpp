#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include "cpu.hpp"
#include "instruction.hpp"

int main(int argc, char *argv[]){
    std::string binName = argv[1];
    std::cerr << binName; //Cerr for testing, cout actual result
    std::ifstream binStream(argv[1], std::ios::binary);

    CPU mipsCPU;

    binStream.seekg(0, binStream.end);
    int sizeBin = binStream.tellg();
    binStream.seekg(0, binStream.beg);
    //std::cout << sizeBin << '\n';

    char* buffer = new char[0x1000000];
    binStream.read(buffer, sizeBin);
    
    for(int i = 0; i < sizeBin; i++){
        mipsCPU.loadRom(buffer[i], i);
    }
    /*int count = 0;
    while(count < 0x1000000){
        char c;
        binStream.get(c);
        if(c == sizeBin){
        break;
        }
        mipsCPU.loadRom(c, count);
        count++;
    }*/
    
    mipsCPU.run();
    
    //sizeBin = count;
    std::cerr << "i am here" << std::endl;
    return 0;
}
