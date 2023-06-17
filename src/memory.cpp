#include <mos6502/memory.h>


// Definitions for the mos6502::Memory class

mos6502::Memory::Memory()
{
    // At memory instantiation,
    memset(RAM, 0, sizeof(RAM));
}

mos6502::Memory::~Memory() = default;

mos6502::Memory& mos6502::Memory::Initialize()
{
    // Create ONE instance of the memory
    static Memory _self;
    return _self;
}

mos6502::Byte mos6502::Memory::readByteFromRAM(mos6502::Word addr)
{
    // there should be a check for (0 < addr < mos6502::MAX_MEM)
    return RAM[addr];
}

void mos6502::Memory::writeByteToRAM(mos6502::Word addr, mos6502::Byte val)
{
    // there should be a check for (0 < addr < mos6502::MAX_MEM)
    RAM[addr] = val;
}