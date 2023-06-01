# MIPS CPU Simulator and Testbench

This work was done as part of coursework following the specification: https://github.com/m8pple/arch2-2019-cw. This project is a MIPS CPU simulator and testbench designed to accurately execute MIPS-1 big-endian binaries, while the testbench tests the functionality of the simulator at an instruction granularity.

## Features
- Simulates a MIPS CPU and executes MIPS-1 big-endian binaries
- Implements a register file, program counter, and memory
- Loads MIPS binaries into a fixed region of memory for execution
- Supports input and output operations through memory-mapped locations
- Handles exceptions and errors appropriately
- Provides logging capabilities for diagnostic and debugging purposes

## Simulator Input/Output
The simulator is a command-line executable with the following behavior:

- Binary: The path to the MIPS binary file is passed as a command-line parameter to the simulator.
- Input: The input to the simulated binary is provided via the simulator's standard input (stdin). The simulator maps the input into a 32-bit memory location accessible by the binary.
- Output: The output from the simulated binary is produced by writing to a mapped 32-bit memory location. The simulator captures these writes and interprets them as output from the binary.
- Exit: The binary signals successful termination by executing the instruction at address 0. The simulator exits accordingly, using the low 8 bits of register $2 as the return code.
- Exceptions: The simulator handles exceptions that occur when executing illegal instructions, returning appropriate negative exit codes.
- Errors: The simulator handles errors that may occur during execution, such as unimplemented instructions or I/O failures. Error messages are written to stderr.
- Logging: The simulator can emit diagnostic/debugging messages, which should be written to stderr.

## Testbench Build and Execution
To run the testbench, use the following command in the root of the repository:
<pre>
make simulator
</pre>
<pre>
make testbench
</pre>
<pre>
bin/mips_testbench bin/mips_simulator (or make run_tests)
</pre>

The output.csv file will be created in the "test" folder.
