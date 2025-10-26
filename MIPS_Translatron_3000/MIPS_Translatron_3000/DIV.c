/*
* Author: Brady
* Date: 10/26/2025
*/

/*
* CHANGELIST
* - Added comments and formatted
*/

#include "Instruction.h"

void div_reg_assm(void) {
	// Check if opcode matches
	if (strcmp(OP_CODE, "DIV") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	/*
		Checking the type of parameters
	*/

	// The first parameter should be a register
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// The second parameter should be a register
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	/*
		Checking the value of parameters
	*/

	// Rt should be 31 or less
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	// Rs should be 31 or less
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}

	/*
		Putting the binary together
	*/

	// Set the opcode
	setBits_str(31, "000000");

	// Set Rt
	setBits_num(20, PARAM1.value, 5);

	// Set Rs
	setBits_num(25, PARAM2.value, 5);

	// Set the last 6 bits
	setBits_str(5, "011010");

	// Set bits 15-6 to 0
	setBits_num(15, 0, 10);
	
	// tell the system the encoding is done
	state = COMPLETE_ENCODE;
}

void div_reg_bin(void) {
	// Check if the op code bits match
	if (checkBits(31, "000000") != 0 || checkBits(5, "011010") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	/*
		Finding values in the binary
	*/

	// Retrieve Rs
	uint32_t Rs = getBits(25, 5);

	// Retrieve Rt
	uint32_t Rt = getBits(20, 5);

	/*
		Setting Instuciton values
	*/

	// Set the opcode
	setOp("DIV");

	// Set the first parameter to Rt
	setParam(1, REGISTER, Rt);

	// Set the second parameter to Rs
	setParam(2, REGISTER, Rs);

	// tell the system the decoding is done
	state = COMPLETE_DECODE;
}


