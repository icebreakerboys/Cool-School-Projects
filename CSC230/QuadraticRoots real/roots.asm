#Author: Ethan Nicholson
#Date: 03/08/22
#Description: finds the roots of a quadratic function taking
#			  inputs from the stack pointer

.data
eMsg1: .asciiz "There are two roots: "
comma: .asciiz ", "
eMsg2: .asciiz "There is one root: "
eMsg3: .asciiz "There are two complex roots: "
plusminus: .asciiz " +/- "
imaginary: .asciiz "i"

const4: .float 4.0
const2: .float 2.0
constneg1: .float -1.0
const0: .float 0

.text
.globl roots
roots:
	lwc1 $f0, -4($sp) # $f0 = c
	lwc1 $f1, -8($sp) # $f1 = b
	lwc1 $f2, -12($sp) # $f2 = a
	lwc1 $f3, const4 # $f3 = 4
	
	mul.s $f0, $f2, $f0 # $f0 = a * c
	mul.s $f0, $f3, $f0 # $f0 = 4 * a * c
	mul.s $f4, $f1, $f1 # $f5 = b * b
	sub.s $f0, $f4, $f0 # $f4 = (b * b) - (4 * a * c)
	
	lwc1 $f3, const2 # $f3 = 2
	lwc1 $f4, constneg1 # $f4 = -1
	lwc1 $f5, const0 # $f5 = 0
	
	c.le.s $f0, $f5
	bc1t Else1
	sqrt.s $f0, $f0 # $f0 = (b^2 - 4ac)^(1/2)
	mul.s $f1, $f4, $f1 # $f1 = -1 * b
	mul.s $f2, $f3, $f2 # $f2 = 2 * a
	add.s $f3, $f1, $f0 # $f3 = -b + (b^2 - 4ac)^(1/2)
	sub.s $f4, $f1, $f0 # $f4 = -b - (b^2 - 4ac)^(1/2)
	div.s $f0, $f3, $f2 # $f0 = (-b + (b^2 - 4ac)^(1/2))/2a
	div.s $f1, $f4, $f2 # $f0 = (-b - (b^2 - 4ac)^(1/2))/2a
	
	li $v0, 4
	la $a0, eMsg1
	syscall
	li $v0, 2
	mov.s $f12, $f0
	syscall
	li $v0, 4
	la $a0, comma
	syscall
	li $v0, 2
	mov.s $f12, $f1
	syscall
	
	j After
	
	Else1: 	c.eq.s $f0 $f5
		bc1f Else2
		sqrt.s $f0, $f0 # $f0 = (b^2 - 4ac)^(1/2)
		mul.s $f1, $f4, $f1 # $f1 = -1 * b
		mul.s $f2, $f3, $f2 # $f2 = 2 * a
		add.s $f0, $f1, $f0 # $f0 = -b + (b^2 - 4ac)^(1/2)
		div.s $f0, $f0, $f2 # $f0 = (-b + (b^2 - 4ac)^(1/2))/2a
	
		li $v0, 4
		la $a0, eMsg2
		syscall
		li $v0, 2
		mov.s $f12, $f0
		syscall 
		
		j After
	
	Else2:	mul.s $f0, $f4, $f0 # $f0 = -(b^2 - 4ac) (which is postive because we know the discriminant is negative)
		sqrt.s $f0, $f0 # $f0 = (b^2 - 4ac)^(1/2)
		mul.s $f1, $f4, $f1 # $f1 = -1 * b
		mul.s $f2, $f3, $f2 # $f2 = 2 * a
		div.s $f0, $f0, $f2
		div.s $f1, $f1, $f2
		
		li $v0, 4
		la $a0, eMsg3
		syscall
		li $v0, 2
		mov.s $f12, $f1
		syscall 
		li $v0, 4
		la $a0, plusminus
		syscall
		li $v0, 2
		mov.s $f12, $f0
		syscall 
		li $v0, 4
		la $a0, imaginary
		syscall
		
	After:
	
	jr $ra
