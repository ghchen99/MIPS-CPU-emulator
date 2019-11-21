all: simulator

simulator: bin/simulator

bin/simulator: bin/instruction.o bin/cpu.o bin/simulator.o
	g++ $^ -o ./bin/mips_simulator
	
bin/instruction.o: src/instruction.cpp src/instruction.hpp
	g++ -c src/instruction.cpp -o bin/instruction.o

	
bin/cpu.o: src/cpu.cpp src/cpu.hpp src/instruction.hpp
	g++ -c src/cpu.cpp -o bin/cpu.o

bin/simulator.o: src/simulator.cpp
	g++ -c src/simulator.cpp - o bin/simulator.o

run:
	./simulator

clean: rm *.o simulator
