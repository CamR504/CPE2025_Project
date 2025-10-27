/*
* Author: Brady
* Date: 10/27/2025
*/

/*
* CHANGELIST
* - Commented and formatted
*/

#include "Instruction.h"

void or_reg_assm(void) {
	// Check the opcode
	if (strcmp(OP_CODE, "OR") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	/*
		Checking the type of parameters 
	*/

	// Generally the first parameter should always be a register
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// Second parameter should be a register
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// Third parameter should be a register
	if (PARAM3.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	/*
		Checking the value of parameters
	*/

	// Rd should be 31 or less
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	// Rs should be 31 or less
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}

	// Rt should be 31 or less
	if (PARAM3.value > 31) {
		state = INVALID_REG;
		return;
	}

	/*
		Putting the binary together
	*/

	// Set the opcode
	setBits_num(31, 0, 6);
	setBits_str(5, "100101");

	// Set Rd
	setBits_num(15, PARAM1.value, 5);

	// Set Rs
	setBits_num(25, PARAM2.value, 5);

	// Set Rt
	setBits_num(20, PARAM3.value, 5);

	// tell the system the encoding is done
	state = COMPLETE_ENCODE;
}

void or_reg_bin(void) {
	// Check the opcode
	if (checkBits(31, "000000") != 0 || checkBits(5, "100101") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	/*
		Finding values in the binary
	*/

	// get Rd
	uint32_t Rd = getBits(15, 5);

	// Get Rs
	uint32_t Rs = getBits(25, 5);

	// Get Rt
	uint32_t Rt = getBits(20, 5);

	/*
		Setting Instuciton values
	*/

	// Set opcode
	setOp("OR");

	// Set the first parameter
	setParam(1, REGISTER, Rd);
	
	// Set the second parameter
	setParam(2, REGISTER, Rs); 

	// Set the third parameter
	setParam(3, REGISTER, Rt); 

	// tell the system the decoding is done
	state = COMPLETE_DECODE;
}


