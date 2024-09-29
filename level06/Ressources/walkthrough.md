# Level06

## Setup

We find a binary file at the root of the user **`level06`** named *`./level06`*.

```bash
scp -r -P 4242 level06@<vm_ip>:/home/users/level06/level06 .
```

### Hex-Rays

We used the Hex-Rays output on the [Dogbolt website](https://dogbolt.org/).

## Source
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

In the function `auth(s, serial)`:

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

Let's juste recompile this code to know the necessary serial for a string s (code in main.c)


## Solution
	> gcc main.c
	> ./a.out MonSuperLogin
	Login: MonSuperLogin
	Serial: 6236440

In the VM:

	> ./level06
	...
	> MonSuperLogin
	...
	> 6236440
	Authenticated!
	> cat /home/users/level07/.pass
	GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8