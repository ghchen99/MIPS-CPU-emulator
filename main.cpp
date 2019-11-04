#include <string>
#include <fstream>
#include <iostream>

void add(uint32_t a, uint32_t b){
  uint32_t c = a + b;
  std::cout << c << '\n';
  //r[3] = r[1] + r[2];
}

//std::vector<uint32_t> r(32);

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
