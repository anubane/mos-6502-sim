#include <mos6502/mos6502_exceptions.h>

mos6502::RAMException::RAMException(char* msg) : message(msg) {;}

mos6502::RAMException::~RAMException() = default;

const char* mos6502::RAMException::what() const noexcept
{
    return message;
}