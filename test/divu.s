#exit code 9

addi $3, $0, 4
addi $4, $0, 5

divu $2, $3, $4
mfhi
mflo

add $2 mfhi mflo 

jr $0
