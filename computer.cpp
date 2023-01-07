#include "computer.hpp"

int convert_to_int(unsigned_int in){
	int res = 0;
	for(int i = 0; i < BITS; i++){
		if(in.bits[i]){
			res += pow(2,i);
		}
	}
	return res;
}

unsigned_int bool_to_unsigned(bool in){
	unsigned_int ret = UINT_NULL;
	ret.bits[0] = in;
	return ret;
}

bool checkOverflow(unsigned_int x){
	for(int i = 0; i < BITS; i++){
		if(!x.bits[i]){
			return false;
		}
	}
	return true;
}

void showBits(unsigned_int in){
	for(int i = 0; i < BITS; i++){
		std::cout << in.bits[i];
	}
	std::cout << "\n";
}

void computerInstance::start(){
	for(int i = 0; i < pow(2,BITS); i++){
		REGISTER[i] = 0;
		RAM[i] = 0;
	}
	RAM[RAMPTR_ADDR] = {0,0,0,1,0,0,0,0};
}

void computerInstance::dump(){
	std::cout << "RAM : Decimal : Binary \n";
	for(int i = 0; i < pow(2,BITS); i++){
		std::cout << std::setw(5) <<  i << " : " << std::setw(5) << RAM[i] << " : ";
		showBits(RAM[i]);
	}
	std::cout << "Register : Decimal : Binary \n";
	for(int i = 0; i < pow(2,BITS); i++){
		std::cout << std::setw(5) << i << " : " << std::setw(5) << REGISTER[i] << " : ";
		showBits(REGISTER[i]);
	}
	exit(0);
}

void computerInstance::quickDump(){
	std::cout << "RAM : Decimal : Binary \n";
	for(int i = 0; i < 20; i++){
		std::cout << std::setw(5) <<  i << " : " << std::setw(5) << RAM[i] << " : ";
		showBits(RAM[i]);
	}
	std::cout << "Register : Decimal : Binary \n";
	for(int i = 0; i < 20; i++){
		std::cout << std::setw(5) << i << " : " << std::setw(5) << REGISTER[i] << " : ";
		showBits(REGISTER[i]);
	}
	exit(0);
}

unsigned_int computerInstance::GET_R(unsigned_int addr){
	return REGISTER[addr];
}

unsigned_int computerInstance::GET(unsigned_int addr){
	return RAM[addr];
}

void computerInstance::REG(unsigned_int val, unsigned_int addr){
	REGISTER[addr] = val;
}

void computerInstance::PUSH(unsigned_int x){
	REG(RAMPTR,UINT_NULL);
	RAM[RAMPTR] = x;
	ITERATE(RAMPTR_ADDR);
}

void computerInstance::PUSH(){
	PUSH(UINT_NULL);
}

void computerInstance::POP(){
	DEITERATE(RAMPTR_ADDR);
	REG(GET(RAMPTR),UINT_NULL);
}

void computerInstance::ITERATE(unsigned_int addr_x){
	for(int i = 0; i < BITS; i++){
		RAM[addr_x].bits[i] = !GET(addr_x).bits[i];
		if(GET(addr_x).bits[i])
			return;
	}
}


void computerInstance::DEITERATE(unsigned_int addr_x){
	for(int i = 0; i < BITS; i++){
		RAM[addr_x].bits[i] = !GET(addr_x).bits[i];
		if(!GET(addr_x).bits[i])
			return;
	}
}

void computerInstance::ADD(unsigned_int addr_x, unsigned_int addr_y){
	PUSH();
	unsigned_int addr_ret = GET_R(UINT_NULL);
	PUSH();
	unsigned_int addr_carry = GET_R(UINT_NULL);
	for(int i = 0; i < BITS; i++){
		RAM[addr_ret].bits[i] = (RAM[addr_x].bits[i] xor RAM[addr_y].bits[i]) xor RAM[addr_carry].bits[0];
		// add x, y and carry together mod 2 
		RAM[addr_carry] = (RAM[addr_x].bits[i] && RAM[addr_y].bits[i]) || ((RAM[addr_x].bits[i] xor RAM[addr_y].bits[i]) && RAM[addr_carry]);
		// turn on the carry bit if :
		// both x and y are on (1 + 1 = 0 carry 1)
		// if the result of x and y being added mod 2 is 1 and the carry (from the previous bit)
		// is on (ex. (1 + 0) + 1 carry = 0 carry 1)
	}
	POP();
	POP();
	REG(GET(addr_ret), UINT_NULL);
}

void computerInstance::SUB(unsigned_int addr_x, unsigned_int addr_y){
	PUSH();
	unsigned_int addr_ret = GET_R(UINT_NULL);
	PUSH();
	unsigned_int addr_borrow = GET_R(UINT_NULL);
	for(int i = 0; i < BITS; i++){
		RAM[addr_ret].bits[i] = (RAM[addr_x].bits[i] xor RAM[addr_y].bits[i]) xor RAM[addr_borrow];
		RAM[addr_borrow] = !(RAM[addr_x].bits[i] && !RAM[addr_borrow]) && RAM[addr_y].bits[i];
	}
	POP();
	POP();
	REG(RAM[addr_ret], UINT_NULL);
} 

void computerInstance::COM(unsigned_int addr_x, unsigned_int addr_y){
	for(int i = 0; i < BITS; i++){
		if(RAM[addr_x].bits[i] xor RAM[addr_y].bits[i]){
			REG(UINT_NULL, UINT_NULL);
			return;
		}
	}
	REG({1,0,0,0,0,0,0,0}, UINT_NULL);
}

void computerInstance::MUL(unsigned_int addr_x, unsigned_int addr_y){
	PUSH();
	unsigned_int addr_ret = GET_R(UINT_NULL);
	PUSH();
	unsigned_int addr_iterator = GET_R(UINT_NULL);
	COM(addr_iterator,addr_y);
	while(!GET_R(UINT_NULL)){
		ADD(addr_ret,addr_x);
		RAM[addr_ret] = GET_R(UINT_NULL);

		ITERATE(addr_iterator);
		COM(addr_iterator,addr_y);
	}
	POP();
	POP();
	POP();
	REG(RAM[addr_ret],UINT_NULL);
}

void computerInstance::DIV(unsigned_int addr_x, unsigned_int addr_y){ // x/y = res 
	std::cout << "dividend = " << GET(addr_x) << "\ndivisor = " << GET(addr_y) << "\n";
	PUSH({1,0,0,0,0,0,0,0});
	unsigned_int addr_iterator = GET_R(UINT_NULL);
	std::cout << "iterator = " << GET(addr_iterator) << "\n";
	MUL(addr_iterator,addr_y);
	COM(GET_R(UINT_NULL),addr_x);
	while(!GET_R(UINT_NULL)){
		ITERATE(addr_iterator);
		std::cout << "iterator = " << GET(addr_iterator) << "\n";
		MUL(addr_x,addr_y);
		std::cout << GET_R(UINT_NULL) << " = " << GET(addr_iterator) << " * " << GET(addr_y) << "\n";
		COM(GET_R(UINT_NULL),addr_x);
	}
	POP();
	POP();
	POP();
	REG(GET(addr_iterator),UINT_NULL);
}
