/* 
Shitty little endian CPU by cattodoameow
Limitations :
    - no constants (cant be like ADD(1,2), have to put them into variables)
    - slow
    - limited instruction set
    - shitty
    - liable to crash at any point
    - zero, as in zilch, nada, security
    (don't, if you were so inclined for whatever reason, use this for sensitive things)
*/

#include "instructions.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>
const unsigned int BITS = 16;
#define _UINT_MAX {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0}
#define UINT_NULL {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
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
    void operator =(unsigned in){
        for(int i = 0; i < BITS; i++){
            bits[i] = in % (int)pow(2,i);
        }
    }
};

int convert_to_int(unsigned_int in); // these ones aren't supposed to be instructions, they're just here to make coding this easier lol

unsigned_int bool_to_unsigned(bool in);

bool checkOverflow(unsigned_int x);

void showBits(unsigned_int x);

class computerInstance{
public :
    unsigned_int REGISTER[5] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
    // A - accumulator
    // B - program counter
    // C - general purpose
    // D - general purpose
    // E - general purpose

    void next(); // run next operation
    
    unsigned_int RAM[256];
    // addresses 0 - 32 is stack
    // addresses 33 - 255 is heap
    unsigned_int RAMPTR_ADDR = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    void init(); // initializes the computer
    
    void dump(); // dumps memory and exits

    void STP();

    void JMP(unsigned_int addr);
    
    void JZ(unsigned_int addr);

    void JNZ(unsigned_int addr);  


    void INC(unsigned_int addr_x);

    void DEC(unsigned_int addr_x);

    void ADD(unsigned_int addr_x, unsigned_int addr_y); 

    void SUB(unsigned_int addr_x, unsigned_int addr_y); 

    void MUL(unsigned_int addr_x, unsigned_int addr_y); 

    void DIV(unsigned_int addr_x, unsigned_int addr_y);

    void COM(unsigned_int addr_x, unsigned_int addr_y); 


    
    unsigned_int GETR(unsigned_int addr);

    void LDA(unsigned_int val);

    void MVC();

    void MVD();

    void MVE();

    void MVR(unsigned_int addr);
};
