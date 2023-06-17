#include <mos6502/commons.h>
#include <mos6502/architecture.h>
#include <mos6502/instructions.h>
#include <mos6502/mos6502_exceptions.h>


// Defining members of the mos6502::CPU class

mos6502::CPU::CPU()
{
    // TODO ?
}

mos6502::CPU::~CPU() = default;

mos6502::CPU& mos6502::CPU::MakeCPU()
{
    // Create ONE instance of the CPU
    static CPU _self;
    return _self;
}

// Register update functions
// Processor Status Flag getters of mos6502::CPU class
bool mos6502::CPU::getCryFlg()
{
    // Bit 0 -> Carry Flag
    // AND with Carry Flag Mask
    mos6502::Byte _temp = ProcStatusFlg.getRegisterVal() &
                            mos6502::ProcStatusFlag::CRYFLG;
    return _temp == mos6502::ProcStatusFlag::CRYFLG;
}

bool mos6502::CPU::getZroFlg()
{
    // Bit 1 -> Zero Flag
    // AND with Zero Flag Mask
    mos6502::Byte _temp = ProcStatusFlg.getRegisterVal() &
                            mos6502::ProcStatusFlag::ZROFLG;
    return _temp == mos6502::ProcStatusFlag::ZROFLG;
}

bool mos6502::CPU::getIrqDis()
{
    // Bit 2 -> Interrupt Disable
    // AND with Interrupt Disable Flag Mask
    mos6502::Byte _temp = ProcStatusFlg.getRegisterVal() &
                            mos6502::ProcStatusFlag::IRQDIS;
    return _temp == mos6502::ProcStatusFlag::IRQDIS;
}

bool mos6502::CPU::getDecMod()
{
    // Bit 3 -> Decimal Mode
    // AND with Decimal Mode Flag Mask
    mos6502::Byte _temp = ProcStatusFlg.getRegisterVal() &
                            mos6502::ProcStatusFlag::DECMOD;
    return _temp == mos6502::ProcStatusFlag::DECMOD;
}

bool mos6502::CPU::getBrkCom()
{
    // Bit 4 -> Break Command
    // AND with Break Command Flag Mask
    mos6502::Byte _temp = ProcStatusFlg.getRegisterVal() &
                            mos6502::ProcStatusFlag::BRKCOM;
    return _temp == mos6502::ProcStatusFlag::BRKCOM;
}

bool mos6502::CPU::getUnused()
{
    // Bit 5 -> Unused Flag
    // AND with Unused Flag Mask
    mos6502::Byte _temp = ProcStatusFlg.getRegisterVal() &
                            mos6502::ProcStatusFlag::UNUSED;
    return _temp == mos6502::ProcStatusFlag::UNUSED;
}

bool mos6502::CPU::getOvrFlw()
{
    // Bit 6 -> Overflow Flag
    // AND with Overflow Flag Mask
    mos6502::Byte _temp = ProcStatusFlg.getRegisterVal() &
                            mos6502::ProcStatusFlag::OVRFLW;
    return _temp == mos6502::ProcStatusFlag::OVRFLW;
}

bool mos6502::CPU::getNegFlg()
{
    // Bit 7 -> Negative Flag
    // AND with Negative Flag Mask
    mos6502::Byte _temp = ProcStatusFlg.getRegisterVal() &
                            mos6502::ProcStatusFlag::NEGFLG;
    return _temp == mos6502::ProcStatusFlag::NEGFLG;
}

/* Processor Status Flag setters: performs (ProcStatusFlg bitAND val) of 
 * mos6502::CPU class
 */
void mos6502::CPU::setCryFlg(mos6502::FlagMode mod)
{
    if (mod == mos6502::FlagMode::SET)  // set flag as 1
        ProcStatusFlg.setRegisterVal(ProcStatusFlg.getRegisterVal() | 
                                     mos6502::ProcStatusFlag::CRYFLG);
    else if (mod == mos6502::FlagMode::UNSET)  // set flag as 0
        ProcStatusFlg.setRegisterVal(ProcStatusFlg.getRegisterVal() & 
                                     ~mos6502::ProcStatusFlag::CRYFLG);
}

void mos6502::CPU::setZroFlg(mos6502::FlagMode mod)
{
    if (mod == mos6502::FlagMode::SET)  // set flag as 1
        ProcStatusFlg.setRegisterVal(ProcStatusFlg.getRegisterVal() | 
                                     mos6502::ProcStatusFlag::ZROFLG);
    else if (mod == mos6502::FlagMode::UNSET)  // set flag as 0
        ProcStatusFlg.setRegisterVal(ProcStatusFlg.getRegisterVal() & 
                                     ~mos6502::ProcStatusFlag::ZROFLG);
}

void mos6502::CPU::setIrqDis(mos6502::FlagMode mod)
{
    if (mod == mos6502::FlagMode::SET)  // set flag as 1
        ProcStatusFlg.setRegisterVal(ProcStatusFlg.getRegisterVal() | 
                                     mos6502::ProcStatusFlag::IRQDIS);
    else if (mod == mos6502::FlagMode::UNSET)  // set flag as 0
        ProcStatusFlg.setRegisterVal(ProcStatusFlg.getRegisterVal() & 
                                     ~mos6502::ProcStatusFlag::IRQDIS);
}

void mos6502::CPU::setDecMod(mos6502::FlagMode mod)
{
    if (mod == mos6502::FlagMode::SET)  // set flag as 1
        ProcStatusFlg.setRegisterVal(ProcStatusFlg.getRegisterVal() | 
                                     mos6502::ProcStatusFlag::DECMOD);
    else if (mod == mos6502::FlagMode::UNSET)  // set flag as 0
        ProcStatusFlg.setRegisterVal(ProcStatusFlg.getRegisterVal() & 
                                     ~mos6502::ProcStatusFlag::DECMOD);
}

void mos6502::CPU::setBrkCom(mos6502::FlagMode mod)
{
    if (mod == mos6502::FlagMode::SET)  // set flag as 1
        ProcStatusFlg.setRegisterVal(ProcStatusFlg.getRegisterVal() | 
                                     mos6502::ProcStatusFlag::BRKCOM);
    else if (mod == mos6502::FlagMode::UNSET)  // set flag as 0
        ProcStatusFlg.setRegisterVal(ProcStatusFlg.getRegisterVal() & 
                                     ~mos6502::ProcStatusFlag::BRKCOM);
}

void mos6502::CPU::setUnused(mos6502::FlagMode mod)
{
    if (mod == mos6502::FlagMode::SET)  // set flag as 1
        ProcStatusFlg.setRegisterVal(ProcStatusFlg.getRegisterVal() | 
                                     mos6502::ProcStatusFlag::UNUSED);
    else if (mod == mos6502::FlagMode::UNSET)  // set flag as 0
        ProcStatusFlg.setRegisterVal(ProcStatusFlg.getRegisterVal() & 
                                     ~mos6502::ProcStatusFlag::UNUSED);
}

void mos6502::CPU::setOvrFlw(mos6502::FlagMode mod)
{
    if (mod == mos6502::FlagMode::SET)  // set flag as 1
        ProcStatusFlg.setRegisterVal(ProcStatusFlg.getRegisterVal() | 
                                     mos6502::ProcStatusFlag::OVRFLW);
    else if (mod == mos6502::FlagMode::UNSET)  // set flag as 0
        ProcStatusFlg.setRegisterVal(ProcStatusFlg.getRegisterVal() & 
                                     ~mos6502::ProcStatusFlag::OVRFLW);
}

void mos6502::CPU::setNegFlg(mos6502::FlagMode mod)
{
    if (mod == mos6502::FlagMode::SET)  // set flag as 1
        ProcStatusFlg.setRegisterVal(ProcStatusFlg.getRegisterVal() | 
                                     mos6502::ProcStatusFlag::NEGFLG);
    else if (mod == mos6502::FlagMode::UNSET)  // set flag as 0
        ProcStatusFlg.setRegisterVal(ProcStatusFlg.getRegisterVal() & 
                                     ~mos6502::ProcStatusFlag::NEGFLG);
}

// I/O Functions (Access Zero Page)
mos6502::Byte mos6502::CPU::FetchByteFromZroPg(mos6502::UInt32& cycles,
                                               mos6502::Byte lowByte,
                                               mos6502::Memory& mem)
{
    // Add 0x0000 to the lowByte to create target address
    mos6502::Word target_address = 0x0000 + lowByte;
    // Above step ensures we are accessing the Zero Page
    cycles--;
    return mem.readByteFromRAM(target_address);
}

// I/O Functions (Access Stack)
mos6502::Byte mos6502::CPU::PopByteFromStack(mos6502::UInt32& cycles,
                                             mos6502::Memory& mem)
{
    mos6502::Byte stackTop = SP.getRegisterVal();
    try
    {
        if (stackTop == 0xFF)
            throw mos6502::RAMException(mos6502::stk_empty);

        // Add 0x0100 to the lowByte to create target address
        mos6502::Word target_address = 0x0100 + stackTop;
        // Above step ensures we are accessing the Stack Region
        ++SP;   // Stack grows from high mem to low mem
        cycles--;
        return mem.readByteFromRAM(target_address);
        // Above operation must be accompanied with updation of the Stack Pointer
    }
    catch(const mos6502::RAMException e)
    {
        std::cerr << e.what();
    }
}

void mos6502::CPU::PushByteOnStack(mos6502::UInt32& cycles,
                                   mos6502::Byte value,
                                   mos6502::Memory& mem)
{
    mos6502::Byte stackTop = SP.getRegisterVal();
    try
    {
        if (stackTop == 0x00)
            throw mos6502::RAMException(mos6502::stk_full);
            
        // Add 0x0100 to the lowByte to create target address
        mos6502::Word target_address = 0x0100 + stackTop;
        // Above step ensures we are accessing the Stack Region
        --SP;   // Stack grows from high mem to low mem
        cycles--;
        mem.writeByteToRAM(target_address, value);
        // Above operation must be accompanied with updation of the Stack Pointer
    }
    catch(const mos6502::RAMException e)
    {
        std::cerr << e.what();
    }
}

// I/O Functions (Access Peripherals)

// I/O Functions (Access RAM)
mos6502::Byte mos6502::CPU::FetchByteFromMem_PC(mos6502::UInt32& cycles, 
                                                mos6502::Memory& mem)
{
    mos6502::Word target_addr = PC.getRegisterVal();
    try 
    {
        if (0x0600 > target_addr || target_addr > 0xFFF9)
            throw mos6502::RAMException(mos6502::ram_access_fail);
    
        // Get instruction at current PC value and increment PC
        mos6502::Byte data = mem.readByteFromRAM(PC.getRegisterVal());
        ++PC;   // pre-increment operator is overloaded
        cycles--;
        return data;
    }
    catch (const mos6502::RAMException e)
    {
        //do something with e
        std::cerr << e.what();
    }
}

mos6502::Byte mos6502::CPU::FetchByteFromMem_Addr(mos6502::UInt32& cycles,
                                                  mos6502::Word addr,
                                                  mos6502::Memory& mem)
{
    try 
    {
        if (0x0600 > addr || addr > 0xFFF9)
            throw mos6502::RAMException(mos6502::ram_access_fail);
        
        // Get data at current PC value but DO NOT increment PC
        mos6502::Byte data = mem.readByteFromRAM(addr);
        cycles--;
        return data;
    }
    catch (const mos6502::RAMException e)
    {
        //do something with e
        std::cerr << e.what();
    }
}

mos6502::Word mos6502::CPU::FetchWordFromMem_PC(mos6502::UInt32& cycles,
                                                mos6502::Memory& mem)
{
    /* 6502 is Little Endian, LSB is stored at x, MSB at x+a
     * Get instruction at current PC value and increment PC
     */
    mos6502::Word target_addr = PC.getRegisterVal();
    try 
    {
        if (0x0600 > target_addr || target_addr > 0xFFF9)
            throw mos6502::RAMException(mos6502::ram_access_fail);
    
        //Reading in he Low Byte
        mos6502::Word data = mem.readByteFromRAM(target_addr);
        ++PC;   // pre-increment operator is overloaded
        cycles--;   // Memory fetch cycle consumed

        target_addr = PC.getRegisterVal();
        //Reading in the High Byte
        data |= (mem.readByteFromRAM(target_addr)
                    << (mos6502::Byte)8);
        /* The 8 bit shift ensures that the data moves to MS byte */
        ++PC;   // pre-increment operator is overloaded
        cycles--;

        return data;
    }
    catch (const mos6502::RAMException e)
    {
        //do something with e
        std::cerr << e.what();
    }
}

mos6502::Word mos6502::CPU::FetchWordFromMem_Addr(mos6502::UInt32& cycles,
                                                  mos6502::Word addr,
                                                  mos6502::Memory& mem)
{
    try 
    {
        if (0x0600 > addr || addr > 0xFFF9)
            throw mos6502::RAMException(mos6502::ram_access_fail);
    }
    catch (const mos6502::RAMException e)
    {
        //do something with e
        std::cerr << e.what();
    }
}

// I/O Functions (H/W Interrupts)

// CPU Interface Functions
void mos6502::CPU::Reset(mos6502::Memory &mem)
{
    /* Reset sequence emulated from (somewhat - not exact)
     * https://www.c64-wiki.com/wiki/Reset_(Process)    --scratched--
     * http://6502.cdot.systems/
     * The values are obtained from the website above
     */ 

    PC.setRegisterVal(0x0600);    // 16-bit

    A.setRegisterVal(0x00);     // 8-bit
    X.setRegisterVal(0x00);     // 8-bit
    Y.setRegisterVal(0x00);     // 8-bit
    SP.setRegisterVal(0xFF);    // 8-bit

    /* Setting the Reserved and Break Command Flags and unsetting others */
    ProcStatusFlg.setRegisterVal(0x30);

    mem.Initialize();
}

void mos6502::CPU::Execute(mos6502::UInt32 cycles, mos6502::Memory &mem)
{
    while (cycles > 0)
    {
        // Cycle 1 spent here
        mos6502::Byte instruction = mos6502::CPU::FetchByteFromMem_PC(cycles,
                                                                      mem);
        // (void)instruction; // dummy use of variable
        switch (instruction)
        {   /* Instruction decode ladder */
        // Load/Store Operations
        case mos6502::ISA::Inst_LDA_IMM:
        {
            mos6502::ISA::simInst_LDA(cycles,
                                      *this,
                                      mem,
                                      mos6502::ADDR_MODES::IMMDVL);
            break;
        }
        case mos6502::ISA::Inst_LDA_ZPG:
        {
            mos6502::ISA::simInst_LDA(cycles,
                                      *this,
                                      mem,
                                      mos6502::ADDR_MODES::ZPGADR);
            break;
        }
        case mos6502::ISA::Inst_LDA_ZPX:
        {
            mos6502::ISA::simInst_LDA(cycles,
                                      *this,
                                      mem,
                                      mos6502::ADDR_MODES::ZPXADR);
            break;
        }
        // Register Transfers
        case mos6502::ISA::Inst_TAX_IMP:
        {
            mos6502::ISA::simInst_TAX(cycles,
                                      *this);
            break;
        }
        case mos6502::ISA::Inst_TXA_IMP:
        {
            mos6502::ISA::simInst_TXA(cycles,
                                      *this);
            break;
        }

        // Stack Operations

        // Logical

        // Arithmetic

        // Increments & Decrements

        // Shifts

        // Jumps & Calls
        case mos6502::ISA::Inst_JSR_ABS:
        {
            mos6502::ISA::simInst_JSR(cycles,
                                      *this,
                                      mem);
            break;
        }

        // Branches

        // Status Flag Changes

        // System Functions

        default:
        {
            printf("\nThe supplied instruction is unknown to the CPU!\n");
            break;
        }    
        }
    }
}