#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_

#include <mos6502/commons.h>


namespace mos6502
{
enum ADDR_MODES
{
    /* Implicit
     * The source and destination is implied by the instruction and no further
     * input required
     */
    IMPLVL,

    /* Accumulator
     * The operand value is available in the Accumulator register
     */
    ACCMVL,
    
    /* Immediate
     * A constant 8 bit value available in the instruction
     */
    IMMDVL,
    
    /* Zero Page
     * only an 8 bit address to the region 0x0000 to 0x00FF is allowed in the
     * instruction (one less fetch cycle - faster)
     */
    ZPGADR,
    
    /* Zero Page, X
     * only an 8 bit address to the region 0x0000 to 0x00FF is allowed in the
     * instruction (one less fetch cycle - faster); to this X register is added
     */
    ZPXADR,
    
    /* Zero Page, Y
     * only an 8 bit address to the region 0x0000 to 0x00FF is allowed in the
     * instruction (one less fetch cycle - faster); to this Y register is added
     */
    ZPYADR,
    
    /* Relative
     * The signed 8 bit value in instruction is added to PC to obtain target adr
     */
    RELTRG,
    
    /* Absolute
     * The target address is available in the instruction
     */
    ABSTRG,
    
    /* Absolute, X
     * Add the contents of X register to the 16 bit address in instruction
     */
    ABSADX,
    
    /* Absolute, Y
     * Add the contents of Y register to the 16 bit address in instruction
     */
    ABSADY,
    
    /* Indirect
     * Instruction contains LS Byte of another address where target address is
     * stored
     */
    INDRCT,
    
    /* Indexed Indirect
     * Address of Table in Zero Page from instruction, X is added with zero page
     * wrap around, to get LS Byte of target address
     */
    IX_IND,
    
    /* Indirect Indexed
     * Instruction has Zero Page location of LS Byte of a 16 bit addr, 
     * Y is added to generate actual target address
     */
    IND_IX
};


class ISA
{
public:
    // Public members
    
    /* ---------------- List of Instructions Opcodes ---------------- */
    static constexpr mos6502::Byte
    // Load/Store Operations
        /* Load Accumulator: Loads a byte of memory into the accumulator
         * setting the zero and negative flags as appropriate.
         */
        Inst_LDA_IMM = 0xA9,    // (1) Immediate; size = 2B, cycles = 2
        Inst_LDA_ZPG = 0xA5,    // (2) Zero Page; size = 2B, cycles = 3
        Inst_LDA_ZPX = 0xB5,    // (3) Zero Page,X; size = 2B, cycles = 4
        Inst_LDA_ABS = 0xAD,    // (4) Absolute; size = 3B, cycles = 4
        Inst_LDA_ABX = 0xBD,    // (5) Absolute,X; size = 3B, cycles = 4 (+1)
        Inst_LDA_ABY = 0xB9,    // (6) Absolute,Y; size = 3B, cycles = 4 (+1)
        Inst_LDA_INX = 0xA1,    // (7) Indirect,X; size = 2B, cycles = 6
        Inst_LDA_INY = 0xB1,    // (8) Indirect,Y; size = 2B, cycles = 5 (+1)
        /* Load X Register: Loads a byte of memory into the X register setting 
         * the zero and negative flags as appropriate.
         */
        Inst_LDX_IMM = 0xA2,    // (9) Immediate; size = 2B, cycles = 2
        Inst_LDX_ZPG = 0xA6,    // (10) Zero Page; size = 2B, cycles = 3
        Inst_LDX_ZPY = 0xB6,    // (11) Zero Page,Y; size = 2B, cycles = 4
        Inst_LDX_ABS = 0xAE,    // (12) Absolute; size = 3B, cycles = 4
        Inst_LDX_ABY = 0xBE,    // (13) Absolute,Y; size = 3B, cycles = 4 (+1)
        /* Load Y Register: Loads a byte of memory into the Y register setting
         * the zero and negative flags as appropriate.
         */
        Inst_LDY_IMM = 0xA2,    // (14) Immediate; size = 2B, cycles = 2
        Inst_LDY_ZPG = 0xA6,    // (15) Zero Page; size = 2B, cycles = 3
        Inst_LDY_ZPX = 0xB6,    // (16) Zero Page,X; size = 2B, cycles = 4
        Inst_LDY_ABS = 0xAE,    // (17) Absolute; size = 3B, cycles = 4
        Inst_LDY_ABX = 0xBE,    // (18) Absolute,X; size = 3B, cycles = 4 (+1)
        /* Store Accumulator: Stores the contents of the accumulator into
         * memory.
         */
        Inst_STA_ZPG = 0x85,    // (19) Zero Page; size = 2B, cycles = 3
        Inst_STA_ZPX = 0x95,    // (20) Zero Page,X; size = 2B, cycles = 4
        Inst_STA_ABS = 0x8D,    // (21) Absolute; size = 3B, cycles = 4
        Inst_STA_ABX = 0x9D,    // (22) Absolute,X; size = 3B, cycles = 5
        Inst_STA_ABY = 0x99,    // (23) Absolute,Y; size = 3B, cycles = 5
        Inst_STA_INX = 0x81,    // (24) Indirect,X; size = 2B, cycles = 6
        Inst_STA_INY = 0x91,    // (25) Indirect,Y; size = 2B, cycles = 6
        /* Store X Register: Stores the contents of the X register into memory.
         */
        Inst_STX_ZPG = 0x86,    // (26) Zero Page; size = 2B, cycles = 3
        Inst_STX_ZPY = 0x96,    // (27) Zero Page,Y; size = 2B, cycles = 4
        Inst_STX_ABS = 0x8E,    // (28) Absolute; size = 3B, cycles = 4
        /* Store Y Register: Stores the contents of the Y register into memory.
         */
        Inst_STY_ZPG = 0x84,    // (29) Zero Page; size = 2B, cycles = 3
        Inst_STY_ZPX = 0x94,    // (30) Zero Page,X; size = 2B, cycles = 4
        Inst_STY_ABS = 0x8C,    // (31) Absolute; size = 3B, cycles = 4

    // Register Transfers
        /* Transfer Accumulator to X: Copies the current contents of the
         * accumulator into the X register and sets the zero and negative
         * flags as appropriate
         */
        Inst_TAX_IMP = 0xAA,    // (32) Implied; size = 1B, cycles = 2
        
        /* Transfer Accumulator to Y: Copies the current contents of the
         * accumulator into the Y register and sets the zero and negative
         * flags as appropriate
         */
        Inst_TAY_IMP = 0xA8,    // (33) Implied; size = 1B, cycles = 2

        /* Transfer X to Accumulator: Copies the current contents of the
         * X register into the accumulator and sets the zero and negative
         * flags as appropriate
         */
        Inst_TXA_IMP = 0x8A,    // (34) Implied; size = 1B, cycles = 2

        /* Transfer Y to Accumulator: Copies the current contents of the
         * Y register into the accumulator and sets the zero and negative
         * flags as appropriate
         */
        Inst_TYA_IMP = 0x98,    // (35) Implied; size = 1B, cycles = 2

    // Stack Operations - Stack between 0x0100 and 0x01FF (fixed MS byte)
        /* Transfer Stack Pointer to X: Copies the current contents of the
         * stack register into the X register and sets the zero and negative
         * flags as appropriate 
         */
        Inst_TSX_IMP = 0xBA,    // (36) Implied; size = 1B, cycles = 2

        /* Transfer X to Stack Pointer: Copies the current contents of the
         * X register into the stack register
         */
        Inst_TXS_IMP = 0x9A,    // (37) Implied; size = 1B, cycles = 2

        /* Push Accumulator: Pushes a copy of the accumulator on to the stack
         */
        Inst_PHA_IMP = 0x48,    // (38) Implied; size = 1B, cycles = 3
        
        /* Push Processor Status: Pushes a copy of the status flags on
         * to the stack
         */
        Inst_PHP_IMP = 0x08,    // (39) Implied; size = 1B, cycles = 3
        
        /* Pull Accumulator: Pulls an 8 bit value from the stack and into the 
         * accumulator. The zero and negative flags are set as appropriate
         */
        Inst_PLA_IMP = 0x68,    // (40) Implied; size = 1B, cycles = 4
        
        /* Pull Processor Status: Pulls an 8 bit value from the stack and into
         * the processor flags. The flags will take on new states as determined
         * by the value pulled
         */
        Inst_PLP_IMP = 0x28,    // (41) Implied; size = 1B, cycles = 4
        
    // Logical
        /* Logical AND: A logical AND is performed, bit by bit, on the
         * accumulator contents using the contents of a byte of memory
         */
        Inst_AND_IMM = 0x29,    // (42) Immediate; size = 2B, cycles = 2
        Inst_AND_ZPG = 0x25,    // (43) Zero Page; size = 2B, cycles = 3
        Inst_AND_ZPX = 0x35,    // (44) Zero Page,X; size = 2B, cycles = 4
        Inst_AND_ABS = 0x2D,    // (45) Absolute; size = 3B, cycles = 4
        Inst_AND_ABX = 0x3D,    // (46) Absolute,X; size = 3B, cycles = 4 (+1)
        Inst_AND_ABY = 0x39,    // (47) Absolute,Y; size = 3B, cycles = 4 (+1)
        Inst_AND_INX = 0x21,    // (48) Indirect,X; size = 2B, cycles = 6
        Inst_AND_INY = 0x31,    // (49) Indirect,Y; size = 2B, cycles = 5 (+1) 

        /* Exclusive OR: An exclusive OR is performed, bit by bit, on the
         * accumulator contents using the contents of a byte of memory
         */
        Inst_EOR_IMM = 0x49,    // (50) ; size = 2B, cycles = 2
        Inst_EOR_ZPG = 0x45,    // (51) ; size = 2B, cycles = 3
        Inst_EOR_ZPX = 0x55,    // (52) ; size = 2B, cycles = 4
        Inst_EOR_ABS = 0x4D,    // (53) ; size = 3B, cycles = 4
        Inst_EOR_ABX = 0x5D,    // (54) ; size = 3B, cycles = 4 (+1)
        Inst_EOR_ABY = 0x59,    // (55) ; size = 3B, cycles = 4 (+1)
        Inst_EOR_INX = 0x41,    // (56) ; size = 2B, cycles = 6
        Inst_EOR_INY = 0x51,    // (57) ; size = 2B, cycles = 5 (+1)
        
        /* Logical Inclusive OR: An inclusive OR is performed, bit by bit, on
         * the accumulator contents using the contents of a byte of memory
         */
        Inst_ORA_IMM = 0x09,    // (58) ; size = 2B, cycles = 2
        Inst_ORA_ZPG = 0x05,    // (59) ; size = 2B, cycles = 3
        Inst_ORA_ZPX = 0x15,    // (60) ; size = 2B, cycles = 4
        Inst_ORA_ABS = 0x0D,    // (61) ; size = 3B, cycles = 4
        Inst_ORA_ABX = 0x1D,    // (62) ; size = 3B, cycles = 4 (+1)
        Inst_ORA_ABY = 0x19,    // (63) ; size = 3B, cycles = 4 (+1)
        Inst_ORA_INX = 0x01,    // (64) ; size = 2B, cycles = 6
        Inst_ORA_INY = 0x11,    // (65) ; size = 2B, cycles = 5 (+1)

        /* Bit Test: This instructions is used to test if one or more bits are
         * set in a target memory location. The mask pattern in A is ANDed with
         * the value in memory to set or clear the zero flag, but the result is
         * not kept. Bits 7 and 6 of the value from memory are copied into the
         * N and V flags
         */
        Inst_BIT_ZPG = 0x24,    // (66) Zero Page; size = 2B, cycles = 3
        Inst_BIT_ABS = 0x2C,    // (67) Absolute; size = 3B, cycles = 4
        
    // Arithmetic
        /* Add with Carry: This instruction adds the contents of a memory
         * location to the accumulator together with the carry bit. If overflow
         * occurs the carry bit is set, this enables multiple byte addition to
         * be performed
         */
        Inst_ADC_IMM = 0x69,    // (68) Immediate; size = 2B, cycles = 2
        Inst_ADC_ZPG = 0x65,    // (69) Zero Page; size = 2B, cycles = 3
        Inst_ADC_ZPX = 0x75,    // (70) Zero Page,X; size = 2B, cycles = 4
        Inst_ADC_ABS = 0x6D,    // (71) Absolute; size = 3B, cycles = 4
        Inst_ADC_ABX = 0x7D,    // (72) Absolute,X; size = 3B, cycles = 4 (+1)
        Inst_ADC_ABY = 0x79,    // (73) Absolute,Y; size = 3B, cycles = 4 (+1)
        Inst_ADC_INX = 0x61,    // (74) Indirect,X; size = 2B, cycles = 6
        Inst_ADC_INY = 0x71,    // (75) Indirect,Y; size = 2B, cycles = 5 (+1)

        /* Subtract with Carry: This instruction subtracts the contents of a
         * memory location to the accumulator together with the not of the
         * carry bit. If overflow occurs the carry bit is clear, this enables
         * multiple byte subtraction to be performed
         */
        Inst_SBC_IMM = 0xE9,    // (76) Immediate; size = 2B, cycles = 2
        Inst_SBC_ZPG = 0xE5,    // (77) Zero Page; size = 2B, cycles = 3
        Inst_SBC_ZPX = 0xF5,    // (78) Zero Page,X; size = 2B, cycles = 4
        Inst_SBC_ABS = 0xED,    // (79) Absolute; size = 3B, cycles = 4
        Inst_SBC_ABX = 0xFD,    // (80) Absolute,X; size = 3B, cycles = 4 (+1)
        Inst_SBC_ABY = 0xF9,    // (81) Absolute,Y; size = 3B, cycles = 4 (+1)
        Inst_SBC_INX = 0xE1,    // (82) Indirect,X; size = 2B, cycles = 6
        Inst_SBC_INY = 0xF1,    // (83) Indirect,Y; size = 2B, cycles = 5 (+1)
        
        /* Compare: This instruction compares the contents of the accumulator
         * with another memory held value and sets the zero and carry flags as
         * appropriate
         */
        Inst_CMP_IMM = 0xC9,    // (84) Immediate; size = 2B, cycles = 2
        Inst_CMP_ZPG = 0xC5,    // (85) Zero Page; size = 2B, cycles = 3
        Inst_CMP_ZPX = 0xD5,    // (86) Zero Page,X; size = 2B, cycles = 4
        Inst_CMP_ABS = 0xCD,    // (87) Absolute; size = 3B, cycles = 4
        Inst_CMP_ABX = 0xDD,    // (88) Absolute,X; size = 3B, cycles = 4 (+1)
        Inst_CMP_ABY = 0xD9,    // (89) Absolute,Y; size = 3B, cycles = 4 (+1)
        Inst_CMP_INX = 0xC1,    // (90) Indirect,X; size = 2B, cycles = 6
        Inst_CMP_INY = 0xD1,    // (91) Indirect,Y; size = 2B, cycles = 5 (+1)

        /* Compare X register: This instruction compares the contents of the X
         * register with another memory held value and sets the zero and carry
         * flags as appropriate
         */
        Inst_CPX_IMM = 0xE0,    // (92) ; size = 2B, cycles = 2
        Inst_CPX_ZPG = 0xE4,    // (93) ; size = 2B, cycles = 3
        Inst_CPX_ABS = 0xEC,    // (94) ; size = 3B, cycles = 4
        
        /* Compare Y Register: This instruction compares the contents of the Y
         * register with another memory held value and sets the zero and carry
         * flags as appropriate
         */
        Inst_CPY_IMM = 0xC0,    // (95) ; size = 2B, cycles = 2
        Inst_CPY_ZPG = 0xC4,    // (96) ; size = 2B, cycles = 3
        Inst_CPY_ABS = 0xCC,    // (97) ; size = 3B, cycles = 4

    // Increments & Decrements
        /* Increment Memory: Adds one to the value held at a specified memory
         * location setting the zero and negative flags as appropriate
         */
        Inst_INC_ZPG = 0xE6,    // (98) ; size = 2B, cycles = 5
        Inst_INC_ZPX = 0xF6,    // (99) ; size = 2B, cycles = 6
        Inst_INC_ABS = 0xEE,    // (100) ; size = 3B, cycles = 6
        Inst_INC_ABX = 0xFE,    // (101) ; size = 3B, cycles = 7

        /* Increment X Register: Adds one to the X register setting the zero
         * and negative flags as appropriate
         */
        Inst_INX_IMP = 0xE8,    // (102) Implied; size = 1B, cycles = 2
        
        /* Increment Y Register: Adds one to the Y register setting the zero
         * and negative flags as appropriate
         */
        Inst_INY_IMP = 0xC8,    // (103) Implied; size = 1B, cycles = 2

        /* Decrement Memory: Subtracts one from the value held at a specified
         * memory location setting the zero and negative flags as appropriate
         */
        Inst_DEC_ZPG = 0xC6,    // (104) ; size = 2B, cycles = 5
        Inst_DEC_ZPX = 0xD6,    // (105) ; size = 2B, cycles = 6
        Inst_DEC_ABS = 0xCE,    // (106) ; size = 3B, cycles = 6
        Inst_DEC_ABX = 0xDE,    // (107) ; size = 3B, cycles = 7
        
        /* Decrement X Register: Subtracts one from the X register setting the
         * zero and negative flags as appropriate
         */
        Inst_DEX_IMP = 0xCA,    // (108) Implied; size = 1B, cycles = 2

        /* Decrement Y Register: Subtracts one from the Y register setting the
         * zero and negative flags as appropriate
         */
        Inst_DEY_IMP = 0x88,    // (109) Implied; size = 1B, cycles = 2
        
    // Shifts
        /* Arithmetic Shift Left: This operation shifts all the bits of the
         * accumulator or memory contents one bit left. Bit 0 is set to 0 and
         * bit 7 is placed in the carry flag. The effect of this operation is
         * to multiply the memory contents by 2 (ignoring 2's complement
         * considerations), setting the carry if the result will not fit in
         * 8 bits
         */
        Inst_ASL_ACC = 0x0A,    // (110) Accumulator; size = 1B, cycles = 2
        Inst_ASL_ZPG = 0x06,    // (111) Zero Page; size = 2B, cycles = 5
        Inst_ASL_ZPX = 0x16,    // (112) Zero Page,X; size = 2B, cycles = 6
        Inst_ASL_ABS = 0x0E,    // (113) Absolute; size = 3B, cycles = 6
        Inst_ASL_ABX = 0x1E,    // (114) Absolute,X; size = 3B, cycles = 7

        /* Logical Shift Right: Each of the bits in A or M is shift one place
         * to the right. The bit that was in bit 0 is shifted into the carry
         * flag. Bit 7 is set to zero
         */
        Inst_LSR_ACC = 0x4A,    // (115) Accumulator; size = 1B, cycles = 2
        Inst_LSR_ZPG = 0x46,    // (116) Zero Page; size = 2B, cycles = 5
        Inst_LSR_ZPX = 0x56,    // (117) Zero Page,X; size = 2B, cycles = 6
        Inst_LSR_ABS = 0x4E,    // (118) Absolute; size = 3B, cycles = 6
        Inst_LSR_ABX = 0x5E,    // (119) Absolute,X; size = 3B, cycles = 7
        
        /* Rotate Left: Move each of the bits in either A or M one place to the
         * left. Bit 0 is filled with the current value of the carry flag
         * whilst the old bit 7 becomes the new carry flag value
         */
        Inst_ROL_ACC = 0x2A,    // (120) Accumulator; size = 1B, cycles = 2
        Inst_ROL_ZPG = 0x26,    // (121) Zero Page; size = 2B, cycles = 5
        Inst_ROL_ZPX = 0x36,    // (122) Zero Page,X; size = 2B, cycles = 6
        Inst_ROL_ABS = 0x2E,    // (123) Absolute; size = 3B, cycles = 6
        Inst_ROL_ABX = 0x3E,    // (124) Absolute,X; size = 3B, cycles = 7

        /* Rotate Right: Move each of the bits in either A or M one place to
         * the right. Bit 7 is filled with the current value of the carry flag
         * whilst the old bit 0 becomes the new carry flag value
         */
        Inst_ROR_ACC = 0x6A,    // (125) Accumulator; size = 1B, cycles = 2
        Inst_ROR_ZPG = 0x66,    // (126) Zero Page; size = 2B, cycles = 5
        Inst_ROR_ZPX = 0x76,    // (127) Zero Page,X; size = 2B, cycles = 6
        Inst_ROR_ABS = 0x6E,    // (128) Absolute; size = 3B, cycles = 6
        Inst_ROR_ABX = 0x7E,    // (129) Absolute,X; size = 3B, cycles = 7
        
    // Jumps & Calls
        /* Jump: Sets the program counter to the address specified by the
         * operand
         */
        Inst_JMP_ABS = 0x4C,    // (130) Absolute; size = 3B, cycles = 3
        Inst_JMP_IND = 0x6C,    // (131) Indirect; size = 3B, cycles = 5

        /* Jump to Subroutine: The JSR instruction pushes the address (minus
         * one) of the return point on to the stack and then sets the program
         * counter to the target memory address
         */
        Inst_JSR_ABS = 0x20,    // (132) Absolute; size = 3B, cycles = 6
        
        /* Return from Subroutine: The RTS instruction is used at the end of a
         * subroutine to return to the calling routine. It pulls the program
         * counter (minus one) from the stack
         */
        Inst_RTS_IMP = 0x60,    // (133) Implied; size = 1B, cycles = 6

    // Branches
        /* Branch if Carry Clear: If the carry flag is clear then add the
         * relative displacement to the program counter to cause a branch to a
         * new location
         */
        Inst_BCC_REL = 0x90,    // (134) Relative; size = 2B, cycles = 2(+1/+2)

        /* Branch if Carry Set: If the carry flag is set then add the relative
         * displacement to the program counter to cause a branch to a new
         * location
         */
        Inst_BCS_REL = 0xB0,    // (135) Relative; size = 2B, cycles = 2(+1/+2)
        
        /* Branch if Equal: If the zero flag is set then add the relative
         * displacement to the program counter to cause a branch to a
         * new location
         */
        Inst_BEQ_REL = 0xF0,    // (136) Relative; size = 2B, cycles = 2(+1/+2)

        /* Branch if Minus: If the negative flag is set then add the relative
         * displacement to the program counter to cause a branch to a
         * new location
         */
        Inst_BMI_REL = 0x30,    // (137) Relative; size = 2B, cycles = 2(+1/+2)
        
        /* Branch if Not Equal: If the zero flag is clear then add the relative
         * displacement to the program counter to cause a branch to a
         * new location
         */
        Inst_BNE_REL = 0xD0,    // (138) Relative; size = 2B, cycles = 2(+1/+2)

        /* Branch if Positive: If the negative flag is clear then add the
         * relative displacement to the program counter to cause a branch to a
         * new location
         */
        Inst_BPL_REL = 0x10,    // (139) Relative; size = 2B, cycles = 2(+1/+2)
        
        /* Branch if Overflow Clear: If the overflow flag is clear then add the
         * relative displacement to the program counter to cause a branch to a
         * new location
         */
        Inst_BVC_REL = 0x50,    // (140) Relative; size = 2B, cycles = 2(+1/+2)

        /* Branch if Overflow Set:If the overflow flag is set then add the
         * relative displacement to the program counter to cause a branch to a
         * new location
         */
        Inst_BVS_REL = 0x70,    // (141) Relative; size = 2B, cycles = 2(+1/+2)
        
    // Status Flag Changes
        /* Clear Carry Flag: Set the carry flag to zero
         */
        Inst_CLC_IMP = 0x18,    // (142) Implied; size = 1B, cycles = 2

        /* Clear Decimal Mode: Sets the decimal mode flag to zero
         */
        Inst_CLD_IMP = 0xD8,    // (143) Implied; size = 1B, cycles = 2
        
        /* Clear Interrupt Disable: Clears the interrupt disable flag allowing
         * normal interrupt requests to be serviced
         */
        Inst_CLI_IMP = 0x58,    // (144) Implied; size = 1B, cycles = 2

        /* Clear Overflow Flag: Clears the overflow flag
         */
        Inst_CLV_IMP = 0xB8,    // (145) Implied; size = 1B, cycles = 2
        
        /* Set Carry Flag: Set the carry flag to one
         */
        Inst_SEC_IMP = 0x38,    // (146) Implied; size = 1B, cycles = 2

        /* Set Decimal Flag: Set the decimal mode flag to one
         */
        Inst_SED_IMP = 0xF8,    // (147) Implied; size = 1B, cycles = 2
        
        /* Set Interrupt Disable: Set the interrupt disable flag to one
         */
        Inst_SEI_IMP = 0x78,    // (148) Implied; size = 1B, cycles = 2

    // System Functions
        /* Force Interrupt: The BRK instruction forces the generation of an
         * interrupt request. The program counter and processor status are
         * pushed on the stack then the IRQ interrupt vector at $FFFE/F is
         * loaded into the PC and the break flag in the status set to one
         */
        Inst_BRK_IMP = 0x00,    // (149) Implied; size = 1B, cycles = 7

        /* No Operation: The NOP instruction causes no changes to the processor
         * other than the normal incrementing of the program counter to the
         * next instruction
         */
        Inst_NOP_IMP = 0xEA,    // (150) Implied; size = 1B, cycles = 2
        
        /* Return from Interrupt: The RTI instruction is used at the end of an
         * interrupt processing routine. It pulls the processor flags from the
         * stack followed by the program counter
         */
        Inst_RTI_IMP = 0x40    // (151) Implied; size = 1B, cycles = 6
    ;    // static constexpr multi-variable declarations/definitions end here

    /* ---------------------- Simulation Engine ---------------------- */
    
    // Processor Status flag update functions
    static void simSetProcStatus_CarryFlag(mos6502::CPU&,
                                           mos6502::Byte);
    static void simSetProcStatus_ZeroFlag(mos6502::CPU&,
                                          mos6502::Byte);
    static void simSetProcStatus_IntrDisblFlag(mos6502::CPU&,
                                               mos6502::Byte);
    static void simSetProcStatus_DecModeFlag(mos6502::CPU&,
                                             mos6502::Byte);
    static void simSetProcStatus_BrkComndFlag(mos6502::CPU&,
                                              mos6502::Byte);
    static void simSetProcStatus_OvrflowFlag(mos6502::CPU&,
                                             mos6502::Byte);
    static void simSetProcStatus_NegFlag(mos6502::CPU&,
                                         mos6502::Byte);

    // Load/Store Operations
    //static void simProcStatus_LDA(mos6502::CPU&, mos6502::Byte);
    static void simInst_LDA(mos6502::UInt32&,
                            mos6502::CPU&,
                            mos6502::Memory&,
                            mos6502::ADDR_MODES);

    // Register Transfers
    //static void simProcStatus_TAX(mos6502::CPU&, mos6502::Byte);
    static void simInst_TAX(mos6502::UInt32&, mos6502::CPU&);

    //static void simProcStatus_TXA(mos6502::CPU&, mos6502::Byte);
    static void simInst_TXA(mos6502::UInt32&, mos6502::CPU&);
/*

    // Stack Operations
    static void simInst_();

    // Logical
    static void simInst_();

    // Arithmetic
    static void simInst_();

    // Increments & Decrements
    static void simInst_();

    // Shifts
    static void simInst_();
*/

    // Jumps & Calls
    static void simInst_JSR(mos6502::UInt32&,
                            mos6502::CPU&,
                            mos6502::Memory&);

/*
    // Branches
    static void simInst_();

    // Status Flag Changes
    static void simInst_();

    // System Functions
    static void simInst_();
*/
};
};

#endif  //INSTRUCTIONS_H_