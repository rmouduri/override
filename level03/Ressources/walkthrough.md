# Level03

## Setup

We find a binary file at the root of the user **`level03`** named *`./level03`*.

```bash
scp -r -P 4242 level03@<vm_ip>:/home/users/level03/level03 .
```

### Hex-Rays

We used the Hex-Rays output on the [Dogbolt website](https://dogbolt.org/).


## Source

We'll follow the important path.

First we test an input.

```C
  test(input, 322424845);
```

And this input is sent to decrypt in some cases.
```C
int  test(int a1, int a2)
{
  int result;

  switch ( a2 - a1 )
  {
    case 1:
    ...
    case 21:
      result = decrypt(a2 - a1); // <---- HERE
      break;
    default:
      result = decrypt(rand());
      break;
  }
  return result;
}
```

These cases are when the number we send is 1 to 21 bellow `322424845`.

So what happens in `decrypt` ?
In `decrypt` we'll spot a string of the same length as the expected string.
And this 'encrypted_string' is transformed during the process with a XOR equal operator.

```C
  strcpy(encrypted_string, "Q}|u`sfg~sf{}|a3");                 // <--- Encrypted version

  for (unsigned int i = 0; i < strlen(encrypted_string); ++i )
    encrypted_string[i] ^= a1;                                  // <--- XOR applyed with the difference between the input and 322424845

  if ( !strcmp(encrypted_string, "Congratulations!") )
    return system("/bin/sh");                                   // <--- /bin/sh if the string matches "Congratulations!"
  else
    return puts("\nInvalid Password");
}
```

This should be easy, let's look at the binary representation of "Q}|u`sfg~sf{}|a3".
The `^=` applies a mask that will basically invert some bits.
Let's find which bits are inverted between the two strings.

```C
"Q}|u`sfg~sf{}|a3" == 01010001 01111101 01111100 01110101 01100000 01110011 01100110 01100111 01111110 01110011 01100110 01111011 01111101 01111100 01100001 00110011
"Congratulations!" == 01000011 01101111 01101110 01100111 01110010 01100001 01110100 01110101 01101100 01100001 01110100 01101001 01101111 01101110 01110011 00100001
```

You will note that every second and fift bit from the right hand side is inverted.
Or `10010` is equal to 18.

### Solution

`322424845 - 18 = 322424827`

```bash
level03@OverRide:~$ ./level03 
***********************************
*		level03		**
***********************************
Password:322424827
$ cat /home/users/level04/.pass   
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
```
