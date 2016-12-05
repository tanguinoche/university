.data

n : .word 3
tab : .word 4, 12, -1, -3, 23, 12, -1, 47

.text
ori $2, $2, 51 # val : $2
ori $8, $8, 6 # i : $8
ori $9, $9, 11 # size : $9

ori $2, $0, 5
syscall #Lecture clavier de val

lui $10, 0x1001
lw $11, 0($10) # chargement de n dans $11
ori $12, $0, 1 #contanste 1
sllv $9, $12, $11 # $9 = size = (1<<n)


#Adresse de tab[0]
addi $10, $15, 0x1001
addi $10, $10, 4 # $10 contient l'adresse de tab[i]

lw $4, 0($10) # on charge le mot à l'adresse $10 dans $4

ori $8, $0, 0 #i=0
loop:
slt $16, $8, $9 #i<size ?
beq $16, $0, endloop # Si non, on va à fin de endloop


slt $16, $4, $2 # tab[i]<val ?
beq $16, $0, else # Si non, on va à else
sub $4, $4, $2 #tab[i] = tab[i] - val
j end
else :
add $4, $4, $2 #tab[i] = tab[i] + val
end:
addi $8, $8, 1 #i++;
lw $4, 0($10) #mot suivant
endloop:


ori $2, $0, 1 # appel systeme
syscall

ori $2, $0, 10
syscall

