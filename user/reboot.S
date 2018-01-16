
  IMPORT AppAddress
  
  EXPORT IrqEnable 
  EXPORT IrqDisable
  EXPORT JMP_Boot
  
  SECTION .text:CODE(2)
  THUMB 
  REQUIRE8
  PRESERVE8

IrqEnable
    CPSIE   I
    MOV     R0, #0
    BX      LR
    
IrqDisable
    CPSID   I
    MOV     R0, #0
    BX      LR

JMP_Boot
   LDR R0, =AppAddress
   LDR SP, [R0]		;Load new stack pointer address
   LDR PC, [R0, #4]	;Load new program counter address
  END