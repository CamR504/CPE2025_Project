/*
* Author: Brady
* Date: 10/26/2025
*/

/*
* CHANGELIST
* - Added comments and formatted
*/

#include "Instruction.h"

void lui_immd_assm(void) {
	// Check if opcode matches
	if (strcmp(OP_CODE, "LUI") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	/*
		Checking the type of parameters
	*/

	// First parameter should be a register
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// Second parameter should be a register
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// Third parameter should be an immediate
	if (PARAM3.type != IMMEDIATE) {
		state = INVALID_PARAM;
		return;
	}

	/*
		Checking the value of parameters
	*/

	// Rt should be less than 31
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	// Rs should be less than 31
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}

	// Immediate should be 16 bits or less
	if (PARAM3.value > 0xFFFF) {
		state = INVALID_IMMED;
		return;
	}

	/*
		Putting the binary together
	*/

	// Set the opcode
	setBits_str(31, "001111");

	// Set Rt
	setBits_num(20, PARAM1.value, 5);

	// Set Rs
	setBits_num(25, PARAM2.value, 5);

	// Set the immediate
	setBits_num(15, PARAM3.value, 16);

	// tell the system the encoding is done
	state = COMPLETE_ENCODE;
}

void lui_immd_bin(void) {
	// Check if the op code bits match
	if (checkBits(31, "001111") != 0) {
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

	// Retrieve immediate
	uint32_t imm16 = getBits(15, 16);

	/*
		Setting Instuciton values
	*/

	// Set the opcode
	setOp("LUI");

	// Set the first parameter to Rt
	setParam(1, REGISTER, Rt); 

	// Set the second parameter to Rs
	setParam(2, REGISTER, Rs); 

	// Set the immediate field
	setParam(3, IMMEDIATE, imm16); 

	// Tell the system the decoding is done
	state = COMPLETE_DECODE;
}



