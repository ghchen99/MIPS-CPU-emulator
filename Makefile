simulator   prog
	mkdir -p bin
	cp $< bin/mips_simulator

all: instruction.o cpu.o main.o 
	g++ instruction.o cpu.o main.o -o prog
	
instruction.o: instruction.cpp instruction.hpp
	g++ -c instruction.cpp

	
cpu.o: cpu.cpp cpu.hpp instruction.hpp
	g++ -c cpu.cpp

main.o: main.cpp
	g++ -c main.cpp

run:
	./prog

clean: rm *.o prog
