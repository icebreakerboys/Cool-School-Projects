#Author: Ethan Nicholson
#Date: 03/08/22
#Description: Takes an integer input to be used with the fizzbuzz function

.data
prompt: .asciiz "Enter an integer: "

.text
.globl main
main:
#print prompt
li $v0, 4
la $a0, prompt
syscall

#read integer
li $v0, 5
syscall

#call FizzBuzz
move $a0, $v0
jal FizzBuzz

#end program
li $v0, 10
syscall