

all: pscx_main
	
pscx_main: pscx_bios.o pscx_cpu.o pscx_instruction.o pscx_interconnect.o pscx_main.o
	g++ -g pscx_bios.o pscx_cpu.o pscx_instruction.o pscx_interconnect.o pscx_main.o -o pscx_main  -std=c++0x


pscx_bios.o: pscx_bios.cpp
	g++ -g -c pscx_bios.cpp -std=c++0x

pscx_cpu.o: pscx_cpu.cpp
	g++ -g -c pscx_cpu.cpp -std=c++0x

pscx_instruction.o: pscx_instruction.cpp
	g++ -g -c pscx_instruction.cpp -std=c++0x

pscx_interconnect.o: pscx_interconnect.cpp
	g++ -g -c pscx_interconnect.cpp -std=c++0x

pscx_main.o: pscx_main.cpp
	g++ -g -c pscx_main.cpp -std=c++0x

clean:
	rm -rf *.o pscx_main

