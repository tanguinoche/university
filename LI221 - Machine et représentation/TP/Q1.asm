.data

n : .word 3
tab : .word 4, 12, -1, -3, 23, 12, -1, 47

.text
ori $2, $2, 51 # val : $2
ori $8, $8, 6 # i : $8
ori $9, $9, 11 # masque : $9

ori $2, $0, 5
syscall #Lecture clavier de val

lui $10, 0x1001
lw $11, 0($10) # chargement de n dans $11
ori $12, $0, 1 #contanste 1
sllv $9, $12, $11 # $9 = size = (1<<n)
addi $9, $9, -1 # masque -1

and $8, $2, $9 # i = val && masque

#Adresse de tab[i]
lui $10, 0x1005 #pointeur sur tab
ori $14, $0, 4 #taille d'un int
mult $2, $14 #i*4
mflo $15 # récupération de i*4 dans $15
add $10, $10, $15 # $10 contient l'adresse de tab[i]

lw $4, 0($10) # on charge le mot à l'adresse $10 dans $4


ori $2, $0, 1 # appel systeme
syscall

ori $2, $0, 10
syscall



