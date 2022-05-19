#Author: Ethan Nicholson
#Date: 03/08/22
#Description: Takes inputs to be used with the roots function

.data
prompt1: .asciiz "Quadratic Solver\na: "
prompt2: .asciiz "b: "
prompt3: .asciiz "c: "

.text
.globl main
main:
	la $a0, prompt1
	jal printAndRead

	la $a0, prompt2
	jal printAndRead

	la $a0, prompt3
	jal printAndRead

	jal roots

	#end program
	li $v0, 10
	syscall

printAndRead:
	li $v0, 4
	syscall
	li $v0, 6
	syscall
	swc1 $f0, 0($sp)
	addi $sp, $sp, 4
	jr $ra
	