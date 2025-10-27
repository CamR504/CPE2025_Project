/*
* Author: Brady
* Date: 10/26/2025
*/

/*
* CHANGELIST
* - Added comments and formatted
*/

#include "Instruction.h"

void lw_immd_assm(void) {
	// Check op code
	if (strcmp(OP_CODE, "LW") != 0) {
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
		state = INVALID_IMMED;
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

	// Rt should be less than 31
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	// Rs should be less than 31
	if ( PARAM3.value > 31) {
		state = INVALID_REG;
		return;
	}

	// Immediate value should be 16 bits or less
	if ( PARAM2.value > 0x7FFF) {
		state = INVALID_IMMED;
		return;
	}
	
	/*
		Putting the binary together
	*/

	// Set the opcode
	setBits_str(31, "100011");

	// Set Rt
	setBits_num(20, PARAM1.value, 5);

	// Set Rs
	setBits_num(25, PARAM3.value, 5);

	// Set immediate
	setBits_num(15, PARAM2.value, 16);

	// tell the system the encoding is done
	state = COMPLETE_ENCODE;
}


void lw_immd_bin(void) {
	//check op code 
	if (checkBits(31, "100011") != 0) {
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
	setOp("LW");

	// Set the first parameter to Rt
	setParam(1, REGISTER, Rt);

	// Set the third parameter to Rs
	setParam(3, REGISTER, Rs);

	// Set the second paraneter to immediate
	setParam(2, IMMEDIATE, imm16);

	// Tell the system the decoding is done
	state = COMPLETE_DECODE;

}
