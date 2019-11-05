#include <string>
#include <fstream>
#include <iostream>

int main(int argc, char *argv[]){
  std::string binName = argv[1];
  std::cerr << binName; //Cerr for testing, cout actual result
  std::ifstream binStream(argv[1], std::ios::binary);

  int count = 0;
  while(count < 0x1000000){
    char c;
    binStream.get(c);
    if(c = NULL){
      break;
    }
    else{
      rom.push_back(c);
    }
    count++;
  }

  int sizeBin = count;

  return 0;
}
