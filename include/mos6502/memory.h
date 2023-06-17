#ifndef MEMORY_H_
#define MEMORY_H_

#include <string.h>
#include <mos6502/commons.h>


namespace mos6502
{
class Memory    // Singleton for our use case
{
private:
// Private members
/* The simulated RAM is essentially an array of Bytes, because the memory
 * is byte addressable
 */
mos6502::Byte RAM[mos6502::MAX_MEM];   // static allocation - fixed memory size
Memory();   // Private constructor to make singleton class (only one object)

public:
//Public members
~Memory();
static Memory& Initialize();

// In the following, using Word as address is 16 bit
mos6502::Byte readByteFromRAM(mos6502::Word); // address
void writeByteToRAM(mos6502::Word, mos6502::Byte); // address, value
};
};

#endif // MEMORY_H_