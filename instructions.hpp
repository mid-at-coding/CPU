#define _STP {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
// stop execution
#define _JMP {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
// set program counter to arg 1
#define _JZ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
// jump if the value in register A is zero, otherwise do nothing
#define _JNZ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
// opposite of JZ


#define _INC {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
// increment register A (the accumulator)
#define _DEC {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
// decrement register A
#define _ADD {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
// adds two values in RAM
#define _SUB {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
// subtracts two values in RAM
#define _MUL {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
// multiplies two values in RAM
#define _DIV {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
// divides two values in RAM
#define _COM {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
// compares two values in RAM


#define _GETR {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
// return RAM value at a certain address
#define _LDA {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
// set register A to a certain value
#define _MVC {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
// set register C to the value of register A
#define _MVD {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
// set register D to the value of register A
#define _MVE {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
// set register E to the value of register A
#define _MVR {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
// set arg 1 in RAM to the value of register A