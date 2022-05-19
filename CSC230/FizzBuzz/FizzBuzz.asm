#Author: Ethan Nicholson
#Date: 03/08/22
#Description: Counts to an integer input, when number is a multiple
#			  of three print fizz, five print buzz, or both print fizzbuzz 

.data
Fizz: .asciiz "Fizz"
Buzz: .asciiz "Buzz" 
Newline: .asciiz "\n"

.text
.globl FizzBuzz
FizzBuzz:
move $t0, $a0
addi $t1, $zero, 1
addi $t2, $zero, 3
addi $t3, $zero, 5
addi $t4, $zero, 1
While:
	#check if $t1 mod 3 == 0
	fizz: 	div $t1, $t2
		mfhi $t5
		bnez $t5, buzz
	
		#print Fizz
		li $v0, 4
		la $a0, Fizz
		syscall
		li $t4, 0
	
	#check if $t1 mod 5 == 0
	buzz: 	div $t1, $t3
		mfhi $t5
		bnez $t5, Else
	
		#print Buzz
		li $v0, 4
		la $a0, Buzz
		syscall
		li $t4, 0
	
	#else print number 
	Else: 	beqz $t4, AfterPrint
		li $v0, 1
		move $a0, $t1
		syscall
		
	AfterPrint:
		#print Newline
		li $v0, 4
		la $a0, Newline
		syscall
	
	#check end condition
	beq $t1, $t0, After
	addi $t4, $zero, 1
	addi $t1, $t1, 1
	j While
After:

jr $ra
