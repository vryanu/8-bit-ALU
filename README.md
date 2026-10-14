# Cpu

**8bit CPU in Logisim + ISA + toolchain**

* Registers REGB00, REGA01, MAR10, ACC11
* Operators ADD000, SUB001, MUL010, DIV011, MOD100, AND101, OR110, XOR111

**ISA**
ART & RAM commands

ART [00000][000 OP]
RAM [00 MOV/SET VAL][MOV][STORE][LOAD][SET][00 MOV/SET LOC]

* ACC acts as RAM output when used as a val
* MOV must be 1 for SET to be used

**Commands Usage**
* MOV [Val] [Loc]
* SET [2 bit number val] [Loc]
* STORE stores a value at the selected address
* LOAD loads a value at the selected address
