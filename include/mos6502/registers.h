#ifndef REGISTERS_H_
#define REGISTERS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mos6502/commons.h>


namespace mos6502
{
enum ProcStatusFlag
{
    CRYFLG = 0x01,  // 0000 0001
    ZROFLG = 0x02,  // 0000 0010
    IRQDIS = 0x04,  // 0000 0100
    DECMOD = 0x08,  // 0000 1000
    BRKCOM = 0x10,  // 0001 0000
    UNUSED = 0x20,  // 0010 0000
    OVRFLW = 0x40,  // 0100 0000
    NEGFLG = 0x80   // 1000 0000
};

class Register8bit
{
private:
    //private members
    mos6502::Byte _reg;

public:
    //public members
    Register8bit();     // Constructor
    ~Register8bit();    // Destructor
    Register8bit& operator++ ();    // prefix (member) increment operator
    Register8bit& operator-- ();    // prefic (member) decrement operator
    mos6502::Byte getRegisterVal();  // Getter
    void setRegisterVal(mos6502::Byte);  // Setter
};


class Register16bit
{
private:
    //private members
    mos6502::Word _reg;

public:
    //public members
    Register16bit();    // Constructor
    ~Register16bit();   // Destructor
    Register16bit& operator++ ();    // prefix (member) increment operator
    mos6502::Word getRegisterVal();  // Getter
    void setRegisterVal(mos6502::Word);  // Setter
};
};

#endif  // REGISTERS_H_