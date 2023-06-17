#include <mos6502/architecture.h>
#include <mos6502/memory.h>



int main(void)
{
    // Setup Processor and (external) Memory
    mos6502::Memory mem = mos6502::Memory::Initialize();
    mos6502::CPU cpu = mos6502::CPU::MakeCPU();

    // Initialize CPU state
    cpu.Reset(mem);
    
    // Programming memory between 0x0600 and 0xFF09
    // Load dummy program to memory
    mem.writeByteToRAM(0x0600,
                       mos6502::ISA::Inst_LDA_ZPG);
    mem.writeByteToRAM(0x0601,
                       0x42);
    mem.writeByteToRAM(0x0042,
                       0x84);
    mem.writeByteToRAM(0x0602,
                       mos6502::ISA::Inst_TAX_IMP);
    mem.writeByteToRAM(0x0603,
                       mos6502::ISA::Inst_TXA_IMP);
    mem.writeByteToRAM(0x0604,
                       mos6502::ISA::Inst_JSR_ABS);
    mem.writeByteToRAM(0x0605,
                       0x0700); //fake 
    
    // Execute the Program
    cpu.Execute(13, mem);   // The cycles correspond to instructions used above
    
    return 0;
}