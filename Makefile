all: simulator

simulator: bin/simulator

bin/simulator: bin/instruction.o bin/cpu.o bin/simulator.o
	g++ $^ -o ./bin/mips_simulator
	
bin/instruction.o: src/instruction.cpp src/instruction.hpp
	g++ -c src/instruction.cpp -o bin/instruction.o

	
bin/cpu.o: src/cpu.cpp src/cpu.hpp src/instruction.hpp
	g++ -c src/cpu.cpp -o bin/cpu.o

bin/simulator.o: src/simulator.cpp
	g++ -c src/simulator.cpp -o bin/simulator.o

run:
	./simulator
	
parser:
	make -C ./test/parser
	chmod u+x ./test/parser/bin/parser

testbench: parser
	mkdir -p ./bin
	cp testbench ./bin/mips_testbench
	chmod u+x ./bin/mips_testbench
	chmod u+x ./test/bingen.sh
	./test/bingen.sh
	

run_tests: simulator testbench
	bin/mips_testbench bin/mips_simulator

clean: rm *.o simulator
