/*
* Author: Brady
* Date: 10/27/2025
*/

/*
* CHANGELIST
* - Fixed the order of parameters being set in the decoding
* - Added comments and formatted
*/

#include "Instruction.h"

void sw_immd_assm(void) {
	// Check opcode
	if (strcmp(OP_CODE, "SW") != 0) {
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

	// The second parameter should be an immediate
	if (PARAM2.type != IMMEDIATE) {
		state = INVALID_PARAM;
		return;
	}

	// The third parameter should be a register
	if (PARAM3.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	/*
		Checking the value of parameters
	*/

	// Rt should be less than 32
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	// The offest should be 16 bits or less
	if (PARAM2.value > 0xFFFF) {
		state = INVALID_IMMED;
		return;
	}

	// Rs should be less than 32
	if (PARAM3.value > 31) {
		state = INVALID_REG;
		return;
	}

	/*
		Putting the binary together
	*/

	// Set the opcode
	setBits_str(31, "101011");

	// Set Rt
	setBits_num(20, PARAM1.value, 5);

	// Set offset
	setBits_num(15, PARAM2.value, 16);

	// Set Rs
	setBits_num(25, PARAM3.value, 5);

	// tell the system the encoding is done
	state = COMPLETE_ENCODE;
}

void sw_immd_bin(void) {
	// Check opcode
	if (checkBits(31, "101011") != 0) {
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

	// Retrieve offset
	uint32_t offset = getBits(15, 16);

	/*
		Setting Instuciton values
	*/

	// Set the opcode
	setOp("SW");

	// Set Rt
	setParam(1, REGISTER, Rt); 

	// Set Rs
	setParam(3, REGISTER, Rs); 

	// Set offset
	setParam(2, IMMEDIATE, offset); 

	// Tell the system the decoding is done
	state = COMPLETE_DECODE;
}