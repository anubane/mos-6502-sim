#include <mos6502/commons.h>
#include <mos6502/architecture.h>
#include <mos6502/instructions.h>

// Processor Status flag update functions
void mos6502::ISA::simSetProcStatus_CarryFlag(mos6502::CPU& cpu,
                                              mos6502::Byte value)
{
    // Set Carry Flag if
}

void mos6502::ISA::simSetProcStatus_ZeroFlag(mos6502::CPU& cpu,
                                             mos6502::Byte value)
{
    // Set Zero Flag if value is zero
    if (value == 0x00) cpu.setZroFlg(mos6502::FlagMode::SET);

}

void mos6502::ISA::simSetProcStatus_IntrDisblFlag(mos6502::CPU& cpu,
                                                  mos6502::Byte value)
{
    // Set Interrupt Disable Flag if
}

void mos6502::ISA::simSetProcStatus_DecModeFlag(mos6502::CPU& cpu,
                                                mos6502::Byte value)
{
    // Set Decimal Mode Flag if
}

void mos6502::ISA::simSetProcStatus_BrkComndFlag(mos6502::CPU& cpu,
                                                 mos6502::Byte value)
{
    // Set Break Command Flag if
}

void mos6502::ISA::simSetProcStatus_OvrflowFlag(mos6502::CPU& cpu,
                                                mos6502::Byte value)
{
    // Set Overflow Flag if 
}

void mos6502::ISA::simSetProcStatus_NegFlag(mos6502::CPU& cpu,
                                            mos6502::Byte value)
{
    // Set Negative Flag if the MSB of value is set
    if ((value & 0b10000000) > 0) cpu.setNegFlg(mos6502::FlagMode::SET);
}

// Load/Store Operations
// void mos6502::ISA::simProcStatus_LDA(mos6502::CPU& cpu, mos6502::Byte accum)
// {
//     /* Affects N, Z */

//     // Set the Negative Flag if MSB bit is 1
//     mos6502::Byte _temp = accum & 0b10000000;
//     if ((accum & 0b10000000) > 0) cpu.invertNegFlg();
//     // Set the Zero Flag if Value is zero
//     if (accum == 0x00) cpu.invertZroFlg();
// }

void mos6502::ISA::simInst_LDA(mos6502::UInt32& cycles,
                               mos6502::CPU& cpu,
                               mos6502::Memory& mem,
                               mos6502::ADDR_MODES mode)
{
    if (mode == mos6502::ADDR_MODES::IMMDVL)
    {
        //Cycle 2 spent here
        mos6502::Byte value = cpu.FetchByteFromMem_PC(cycles, mem);
        cpu.A.setRegisterVal(value);
        //mos6502::ISA::simProcStatus_LDA(cpu, cpu.A.getRegisterVal());
        mos6502::ISA::simSetProcStatus_NegFlag(cpu, cpu.A.getRegisterVal());
        mos6502::ISA::simSetProcStatus_ZeroFlag(cpu, cpu.A.getRegisterVal());
    }
    else if (mode == mos6502::ADDR_MODES::ZPGADR)
    {
        // Cycle 2 spent here
        mos6502::Byte zpgAddress = cpu.FetchByteFromMem_PC(cycles, mem);
        // Cycle 3 spent here
        mos6502::Byte value = cpu.FetchByteFromZroPg(cycles, zpgAddress, mem);
        cpu.A.setRegisterVal(value);
        //mos6502::ISA::simProcStatus_LDA(cpu, cpu.A.getRegisterVal());
        mos6502::ISA::simSetProcStatus_NegFlag(cpu, cpu.A.getRegisterVal());
        mos6502::ISA::simSetProcStatus_ZeroFlag(cpu, cpu.A.getRegisterVal());
    }
    else if (mode == mos6502::ADDR_MODES::ZPXADR)
    {
        // Cycle 2 spent here
        mos6502::Byte zpgAddress = cpu.FetchByteFromMem_PC(cycles, mem);
        // Cycle 3 spent here --> TODO: overflow during addition 
        zpgAddress += cpu.X.getRegisterVal();
        cycles--;
        // Cycle 4 spent here
        mos6502::Byte value = cpu.FetchByteFromZroPg(cycles, zpgAddress, mem);
        cpu.A.setRegisterVal(value);
        //mos6502::ISA::simProcStatus_LDA(cpu, cpu.A.getRegisterVal());
        mos6502::ISA::simSetProcStatus_NegFlag(cpu, cpu.A.getRegisterVal());
        mos6502::ISA::simSetProcStatus_ZeroFlag(cpu, cpu.A.getRegisterVal());
    }
}

// Register Transfers
// void mos6502::ISA::simProcStatus_TAX(mos6502::CPU& cpu, mos6502::Byte accum)
// {
//     /* Affects N, Z */

//     // Set the Negative Flag if MSB bit is 1
//     mos6502::Byte _temp = accum & 0b10000000;
//     if ((accum & 0b10000000) > 0) cpu.invertNegFlg();
//     // Set the Zero Flag if Value is zero
//     if (accum == 0x00) cpu.invertZroFlg();
// }

void mos6502::ISA::simInst_TAX(mos6502::UInt32& cycles, mos6502::CPU& cpu)
{
    //Cycle 2 spent here
    cycles--;
    mos6502::Byte value = cpu.A.getRegisterVal();
    cpu.X.setRegisterVal(value);
    //mos6502::ISA::simProcStatus_TAX(cpu, cpu.X.getRegisterVal());
    mos6502::ISA::simSetProcStatus_NegFlag(cpu, cpu.X.getRegisterVal());
    mos6502::ISA::simSetProcStatus_ZeroFlag(cpu, cpu.X.getRegisterVal());
}

// void mos6502::ISA::simProcStatus_TXA(mos6502::CPU& cpu, mos6502::Byte accum)
// {
//     /* Affects N, Z */

//     // Set the Negative Flag if MSB bit is 1
//     mos6502::Byte _temp = accum & 0b10000000;
//     if ((accum & 0b10000000) > 0) cpu.invertNegFlg();
//     // Set the Zero Flag if Value is zero
//     if (accum == 0x00) cpu.invertZroFlg();
// }

void mos6502::ISA::simInst_TXA(mos6502::UInt32& cycles, mos6502::CPU& cpu)
{
    //Cycle 2 spent here
    cycles--;
    mos6502::Byte value = cpu.X.getRegisterVal();
    cpu.A.setRegisterVal(value);
    //mos6502::ISA::simProcStatus_TAX(cpu, cpu.A.getRegisterVal());
    mos6502::ISA::simSetProcStatus_NegFlag(cpu, cpu.A.getRegisterVal());
    mos6502::ISA::simSetProcStatus_ZeroFlag(cpu, cpu.A.getRegisterVal());
}

// Stack Operations

// Logical

// Arithmetic

// Increments & Decrements

// Shifts

// Jumps & Calls
void mos6502::ISA::simInst_JSR(mos6502::UInt32& cycles,
                               mos6502::CPU& cpu,
                               mos6502::Memory& mem)
{
    //Cycle 2 and 3 spent here (also all 3 bytes of JSR consumed after this)
    mos6502::Word subAddr = cpu.FetchWordFromMem_PC(cycles, mem);
    
    // Cycles 4 and 5 spent below (store PC-1 (?) into the stack region)
    mos6502::Word word_to_push = cpu.PC.getRegisterVal() - 0x0001;
    mos6502::Byte lowByte_to_push = word_to_push & 0x00FF;
    mos6502::Byte highByte_to_push = word_to_push >> (mos6502::Byte)8;
    cpu.PushByteOnStack(cycles, lowByte_to_push, mem);  // push low byte
    cpu.PushByteOnStack(cycles, highByte_to_push, mem);  // push high byte

    // Set value of PC to starting address of sub-routine, 1 cycle spent here
    cpu.PC.setRegisterVal(subAddr);
    cycles--;

    // No change in any status flag
}

// Branches

// Status Flag Changes

// System Functions
