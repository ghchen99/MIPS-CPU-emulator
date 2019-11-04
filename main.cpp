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

  // if(binStream){
  //   binStream.seekg(0, binStream.end);
  //   int sizeBin = -1 + binStream.tellg(); binstream has extra char on end?
  //   std::cout << sizeBin << '\n';
  // }
  //
  // for(int i = 0; i < sizeBin/32; i++){
  //
  // }

  // binStream.close();

  int count = 0;
  while(count < 0x1000000|| count < sizeBin){
    char c;
    binStream.get(c);
    //character to uint_8
    //store in rom
    count++;
  }

  uint32_t x = ul;

  uint32_t a = 1011;
  uint32_t b = 1111;

  add(a, b);

  // switch (/* expression */) {
  //   case /* value */:
  // }

  switch (Instruction.opcode) {
    case Op::rType:
      switch (Instruction.funct) {
        case fun::ADD:{
          std::cout << "ADD" << '\n';
          break;
        }
        case fun::ADDU:{
          std::cout << "ADDU" << '\n';
          break;
        }
        case fun::AND:{
          std::cout << "AND" << '\n';
          break;
        }
      }
  }

  // binStream.seek(seek_end);
  // sizeBin = binStream.tell();
  // std::vector<uint32_t> imem;
  // imem.resize(0x10000000);
  //
  // std::vector<uint32_t> dmem;
  // dmem.resize(0x40000000);
  //
  // binStream.read(&tmp[0], sizeBin);
  //
  // uint32_t registers[32] = {0};
  // uint32_t pc = IMEM_OFFSET; //use constants instead of values
  //
  // while(simulating){
  //   uint32_t instruction;
  //   if( pc == 0 ){
  //
  //   }
  //   else if (oc < IMEM_OFFSET){
  //
  //   }
  //   else if(pc < IMEM_OFFSET + IMEM_LENGTH){
  //     instruction = imem[ pc / 4 ];
  //   }
  //   else{
  //     exit(-1);
  //   }
  // }

  return 0;
}
