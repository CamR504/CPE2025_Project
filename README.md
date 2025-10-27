# CPE2025_Project
C based project for WVU's CPE 310 class
use below to set file path in powershell terminal
Set-Location -Path "[inner MIPS_Translatron_3000 file path]"

use below to compile an exe file to test code
gcc ADD.c ADDI.c AND.c ANDI.c BEQ.c BNE.c DIV.c LUI.c LW.c MFHI.c MFLO.c MIPS_Instruction.c MIPS_Interpreter.c MULT.c OR.c ORI.c SLT.c SLTI.c SUB.c SW.c -o MIPS_Interpreter.exe

*DONE* (examples)
ADD, BNE, ADDI

*DONE* (solved)
SUB (was not writting the correct final 6 bits in the opcode, corrected; BRADY - adjusted opcode)
LW (Comments and fixed logic for immediate check)
LUI (Comments)
DIV (Comments)
AND (Comments and fixed opcode locations for Rs/Rt)
ANDI (Comments)
BEQ (Fixed opcode in the decoding section)

TO DO:
MFHI, MFLO, MULT, OR, ORI, SLT, SLTI, SW
