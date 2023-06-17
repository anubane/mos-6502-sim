#ifndef ARCHITECTURE_H_
#define ARCHITECTURE_H_

#include <mos6502/commons.h>
#include <mos6502/registers.h>
#include <mos6502/memory.h>
#include <mos6502/instructions.h>


namespace mos6502
{
enum FlagMode
{
    UNSET = 0,
    SET = 1
};

class CPU   // Singleton for our use case
{
private:
    // private members
    mos6502::Register16bit PC;   // Program Counter register
    
    mos6502::Register8bit SP; // Stack Pointer register
    mos6502::Register8bit A;  // Accumulator Register
    mos6502::Register8bit X;  // Index X Register
    mos6502::Register8bit Y;  // Index Y Register
    /*
     * Following are the Processor Status Flags Bits
     * ---------------------------------------------
     * # Count starts from right hand side
     * Bit 0 -> Carry Flag
     * Bit 1 -> Zero Flag
     * Bit 2 -> Interrupt Disable
     * Bit 3 -> Decimal Mode
     * Bit 4 -> Break Command
     * Bit 5 -> Unused Flag
     * Bit 6 -> Overflow Flag
     * Bit 7 -> Negative Flag
     */
    mos6502::Register8bit ProcStatusFlg;
    CPU();

    // Instruction Set friend class
    friend class mos6502::ISA;

public:
    // public members
    ~CPU();
    static CPU& MakeCPU();

    // Register update functions

    // Processor Status Flag getters
    bool getCryFlg();
    bool getZroFlg();
    bool getIrqDis();
    bool getDecMod();
    bool getBrkCom();
    bool getUnused();
    bool getOvrFlw();
    bool getNegFlg();
    
    // Processor Status Flag setters: performs (ProcStatusFlg bitAND val)
    void setCryFlg(mos6502::FlagMode);
    void setZroFlg(mos6502::FlagMode);
    void setIrqDis(mos6502::FlagMode);
    void setDecMod(mos6502::FlagMode);
    void setBrkCom(mos6502::FlagMode);
    void setUnused(mos6502::FlagMode);
    void setOvrFlw(mos6502::FlagMode);
    void setNegFlg(mos6502::FlagMode);

    /*
     * Memory in 6502 was comprised of 256 pages of 256 bytes each
     * Page 00: Zero Page, for fast access of the eponymous instructions
     * Page 01: Stack, the 256 byte (fixed) system stack with wrap around
     * Page 02, 03, 04, 05:  (1 KiB of RAM) maybe for peripherals?
     * Page 06 through FF (0600 - FFF9): Random Access program Memory
     * Page FFFA - FFFF: last 6 bytes for Hardware Interrupts
     */
    // I/O Functions (Access Zero Page)
    mos6502::Byte FetchByteFromZroPg(mos6502::UInt32&,     // Cycles
                                     mos6502::Byte,        // Address (low Byte)
                                     mos6502::Memory&);     // Memory object

    // I/O Functions (Access Stack)
    mos6502::Byte PopByteFromStack(mos6502::UInt32&,
                                   mos6502::Memory&);
    void PushByteOnStack(mos6502::UInt32&,  // Cycles
                         mos6502::Byte,     // The data value
                         mos6502::Memory&);  // The Memory Object

    // I/O Functions (Access Peripherals)

    // I/O Functions (Access RAM)
    mos6502::Byte FetchByteFromMem_PC(mos6502::UInt32&, mos6502::Memory&);
    mos6502::Byte FetchByteFromMem_Addr(mos6502::UInt32&,
                                        mos6502::Word,
                                        mos6502::Memory&);
    mos6502::Word FetchWordFromMem_PC(mos6502::UInt32&, mos6502::Memory&);
    mos6502::Word FetchWordFromMem_Addr(mos6502::UInt32&,
                                        mos6502::Word,
                                        mos6502::Memory&);

    // I/O Functions (H/W Interrupts)

    // CPU Interface Functions
    void Reset(mos6502::Memory&);                                
    void Execute(mos6502::UInt32, mos6502::Memory&);
};
};

#endif //ARCHITECTURE_H_ 