Dans les sources:

	unsigned int serial;
	char login[28];
	...
	printf("-> Enter Login: ");
	fgets(login, 32, stdin);
	printf("-> Enter Serial: ");
	scanf("%u", &serial);
	if ( auth(login, serial) )
		return 1;
	puts("Authenticated!");
	system("/bin/sh");

Dans la fonction auth(s, serial):
	v5 = strnlen(s, 32);
	if ( v5 <= 5 )
		return 1;
	v4 = (s[3] ^ 0x1337) + 6221293;
	for ( i = 0; i < v5; ++i )
	{
		if ( s[i] <= 31 )
			return 1;
		v4 += (v4 ^ (unsigned int)s[i]) % 0x539;
	}
	return serial != v4;

Donc on reprend le code ci-dessus pour avoir le serial necessaire a la string s (code dans main.c)

	> gcc main.c
	> ./a.out MonSuperLogin
<<< Login: MonSuperLogin
<<< Serial: 6236440

Dans la vm:
	> ./level06
<<< ...
	> MonSuperLogin
<<< ...
	> 6236440
<<< Authenticated!
	> cat /home/users/level07/.pass
<<< GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8