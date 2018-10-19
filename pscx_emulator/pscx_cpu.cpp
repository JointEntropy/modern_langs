#include "pscx_cpu.h"

#include <iostream>
#include <cassert>


//                
#define assert(message, ...) do { \
    if(!(__VA_ARGS__)) { \
         \
    } \
} while(0)

uint32_t Cpu::load32(uint32_t addr)
{
	return m_inter.load32(addr);
}

void Cpu::store32(uint32_t addr, uint32_t value)
{
	m_inter.store32(addr, value);
}

Cpu::InstructionType Cpu::decodeAndExecute(Instruction instruction)
{
	InstructionType instructionType = INSTRUCTION_TYPE_UNKNOWN;

	switch (instruction.getInstructionCode())
	{
	case /*LUI*/0b001111:
		//---------------------------------
		/*
			LUI -- Load upper immediate
			Description:
			The immediate value is shifted left 16 bits and stored in the register. The lower 16 bits are zeroes
		*/
		// TODO : call LUI instruction.
		// Rust:
		// 0b001111 => self.op_lui(instruction)
		//---------------------------------
		instructionType = opcodeLUI(instruction);
		break;
	case /*ORI*/0b001101:
		instructionType = opcodeORI(instruction);
		break;
	case /*SW*/0b101011:
		instructionType = opcodeSW(instruction);
		break;
	default:
		std::cout << "unhandled instruction 0x" << std::hex << instruction.getInstructionCode() << std::endl;
	}

	return instructionType;
}

//----------------------------------------------
// TODO : to implement the runNextInstruction function.
// It should fetch an instruction at program counter (PC) register,
// increment PC to point to the next instruction and
// execute instruction.
// 
// Rust:
// pub fn run_next instruction(&mut self) {
//     let pc = self.pc;
//
//     Fetch instruction at PC
//     let instruction = self.load32(pc);
//
//     Increment PC to point to the next instruction.
//     self.pc = pc.wrapping_add(4);
//
//     self.decode_and_execute(instruction);
// }
//----------------------------------------------
Cpu::InstructionType Cpu::runNextInstuction()
{ 
	// Fixme
	uint32_t pc = m_pc;
	Instruction instruction = load32(pc);
	printf("Instruction addr %i \n", pc);
	m_pc = pc + 4;
	return decodeAndExecute(instruction);
	//return INSTRUCTION_TYPE_UNKNOWN;
}

//--------------------------------------------------------------
// TODO : to implement the Load Upper Immediate function (LUI).
// It should load the immediate value into the high 16 bits of the target register.
//
// Rust:
// fn op_lui(&mut self, instruction: Instruction)
//     let i = instruction.imm();  load immediate value
//     let t = instruction.t();    load target register
//
//     Low 16 bits are set to 0
//     let v = i << 16;
//
//     self.set_reg(t, v);
// }
//---------------------------------------------------------------
Cpu::InstructionType Cpu::opcodeLUI(Instruction instruction)
{
	uint32_t tmp = instruction.getImmediateValue();
	uint32_t target = instruction.getRegisterTargetIndex();
	uint32_t value = tmp << 16;
	setRegisterValue(target, value);
	return INSTRUCTION_TYPE_LUI;
}

Cpu::InstructionType Cpu::opcodeORI(Instruction instruction)
{
	setRegisterValue(instruction.getRegisterTargetIndex(), instruction.getImmediateValue() | getRegisterValue(instruction.getRegisterSourceIndex()));
	return INSTRUCTION_TYPE_ORI;
}

Cpu::InstructionType Cpu::opcodeSW(Instruction instruction)
{
	uint32_t registerSourceIndex = instruction.getRegisterSourceIndex();
	uint32_t registerTargetIndex = instruction.getRegisterTargetIndex();
	store32(getRegisterValue(registerSourceIndex) + instruction.getSignExtendedImmediateValue(), getRegisterValue(registerTargetIndex));
	return INSTRUCTION_TYPE_SW;
}

uint32_t Cpu::getRegisterValue(uint32_t index) const
{
	// assert(index < _countof(m_regs), "Index out of boundaries");

	if (index >= 32)  //_countof(m_regs)
	{
		printf("Get register value::Index out of boundaries.\n");
	}
	// printf("Get value of %zu\n", &index);
	return m_regs[index];
}

void Cpu::setRegisterValue(uint32_t index, uint32_t value)
{
	// assert(index < _countof(m_regs), "Index out of boundaries");
	if (index >= 32)//_countof(m_regs))
	{
		printf("Set register value::Index out of boundaries.\n");
	}
	// printf("Set %zu with value %zu\n", &index, &value);
	if (index > 0) m_regs[index] = value;
}