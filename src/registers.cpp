#include <mos6502/registers.h>


// Definitions for mos6502::Register8bit class

mos6502::Register8bit::Register8bit() : _reg(0x00) {;}// Constructor}

mos6502::Register8bit::~Register8bit() = default;

mos6502::Register8bit& mos6502::Register8bit::operator++()
{
    // increment the value of _reg by 1
    _reg = _reg + 0x01;
    return *this;
}

mos6502::Register8bit& mos6502::Register8bit::operator--()
{
    // decrement the value of _reg by 1
    _reg = _reg - 0x01;
    return *this;
}

mos6502::Byte mos6502::Register8bit::getRegisterVal()
{
    return _reg;
}

void mos6502::Register8bit::setRegisterVal(mos6502::Byte _val)
{
    _reg = _val;
}



// Definitions for mos6502::Register16bit class

mos6502::Register16bit::Register16bit() : _reg(0x0000) {;}// Constructor}

mos6502::Register16bit::~Register16bit() = default;

mos6502::Register16bit& mos6502::Register16bit::operator++()
{
    // increment the value of _reg by 1
    _reg = _reg + 0x0001;
    return *this;
}

mos6502::Word mos6502::Register16bit::getRegisterVal()
{
    return _reg;
}

void mos6502::Register16bit::setRegisterVal(mos6502::Word _val)
{
    _reg = _val;
}