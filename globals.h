/* ALL THE GLOBAL VARIABLES THE VIRTUAL MACHINE NEEDS*/

#define NUM_REGS 4

// Set up the array of registers

unsigned regs[ NUM_REGS ];

// Set up the array with the program instructions

unsigned program[] = { 0x1064, 0x11C8, 0x2201, 0x0000 };

/* program counter */
int pc = 0;

/* instruction fields */
int instrNum = 0;
int reg1     = 0;
int reg2     = 0;
int reg3     = 0;
int imm      = 0;
