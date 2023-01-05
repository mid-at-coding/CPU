/* 
Shitty CPU by cattodoameow
Limitations :
    - no constants
    - slow
    - limited instruction set
    - shitty
    - liable to crash at any point
    - zero, as in zilch, nada, security
    (don't, if you were so inclined for whatever reason, use this for sensitive things)
*/

#include <iostream>
#include <cmath>
#define BITS 8
#define _UINT_MAX {1,1,1,1,1,1,1,1}
#define UINT_NULL {0,0,0,0,0,0,0,0}
#define RAMPTR GET(RAMPTR_ADDR)
class unsigned_int{
public :
	bool bits[BITS];
	operator unsigned() const{
		unsigned int ret = 0;
		for(int i = 0; i < BITS; i++){
			ret += bits[i] * pow(2,i);
		}
		return ret;
	}
	void operator =(bool in){
		*this = UINT_NULL;
		bits[0] = in;
	}
};

int convert_to_int(unsigned_int in); // these ones aren't supposed to be instructions, they're just placeholders to make coding this easier lol

unsigned_int bool_to_unsigned(bool in);

bool checkOverflow(unsigned_int x);

class computerInstance{
public :
    unsigned_int REGISTER[256]; // address 0 reserved for function output
    unsigned_int RAM[256]; // address 0-7 reserved for system variables
    unsigned_int RAMPTR_ADDR = {1,1,1,0,0,0,0,0}; // stored in ram address 7
    
    void start(); // initializes the computer
    
    unsigned_int GET(unsigned_int addr); // returns the RAM value at the given address

    unsigned_int GET_R(unsigned_int addr); // returns the register value at the given address

    void ITERATE(unsigned_int addr_x); // iterates x in place

    void DEITERATE(unsigned_int addr_x); // deiterates x in place

    void REG(unsigned_int addr_x, unsigned_int addr); // replaces the register at addr with the ram value of addr_x

    void PUSH(unsigned_int x); // adds a variable with the value of x to the stack and puts the address in register 0

    void PUSH(); // adds an uninitialized variable to the stack and puts the address in register 0

    void POP(); // pops the top value of the stack and puts its value in register 0

    void ADD(unsigned_int addr_x, unsigned_int addr_y); // adds two values in RAM and saves the result to register 0

    void SUB(unsigned_int addr_x, unsigned_int addr_y); // subtracts two values in RAM and saves the result to register 0

    void COM(unsigned_int addr_x, unsigned_int addr_y); // checks if two values in RAM are equal and saves the result to register 0

    void MUL(unsigned_int addr_x, unsigned_int addr_y); // multiplies two values in RAM and saves the result to register 0 

    void DIV(unsigned_int addr_x, unsigned_int addr_y); // divides two values in RAM by each other and saves the result to register 0    
};
