/*
* Author: Brady
* Date: 10/26/2025
*/

/*
* CHANGELIST
* - Added comments and formatted
* - Made into a 1 register and one immediate instruction (Cam)
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

	// Second parameter should be an immediate
	if (PARAM2.type != IMMEDIATE) {
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



	// Immediate should be 16 bits or less
	if (PARAM2.value > 0xFFFF) {
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

	// Set Rs as all zeros, not used
	setBits_str(25, "00000");

	// Set the immediate
	setBits_num(15, PARAM2.value, 16);

	// tell the system the encoding is done
	state = COMPLETE_ENCODE;
}

void lui_immd_bin(void) {
	// Check if the op code bits match
	if (checkBits(31, "001111") != 0) {
		state = WRONG_COMMAND;
		return;
	}
	// Check if Rs is all zeros
	if (checkBits(25, "00000") != 0) {
		state = INVALID_PARAM;
		return;
	}

	/*
		Finding values in the binary
	*/

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

 

	// Set the immediate field
	setParam(2, IMMEDIATE, imm16); 
	

	// Tell the system the decoding is done
	state = COMPLETE_DECODE;
}



