#ifndef COMMONS_H_
#define COMMONS_H_

#include <stdint.h>
#include <iostream>

namespace mos6502
{
using Byte = uint8_t; //unsigned char;     // 0 to 255
using Word = uint16_t; //unsigned short;    // 0 to 65,535
using UInt32 = uint32_t; //unsigned int;    // 0 to 4,294,967

// union RAMAccess
// {
//     Byte byte;
//     bool status;
// };

/* Maximum memory length is taken as 64K as per 6502 architecture */
constexpr UInt32 MAX_MEM = (UInt32)(64 * 1024);  // 64 K (maxi memory = 64 KB)

// Forward class declarations
class Register8Bit;
class Register16Bit;
class Memory;
class CPU;
class ISA;

};

#endif  // COMMONS_H_