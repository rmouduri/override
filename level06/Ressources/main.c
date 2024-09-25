#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("Need 1 argument: ./a.out [login]\n");
		return 1;
	} else if (strlen(argv[1]) < 6 || strlen(argv[1]) > 32) {
		printf("Login needs to be length >= 6 and <= 32.\n");
		return 1;
	}

	unsigned int v4;
	char *s = argv[1];
	unsigned int v5 = strlen(s);

	v4 = (s[3] ^ 0x1337) + 6221293;
    for ( int i = 0; i < v5; ++i )
    {
      if ( s[i] <= 31 )
        return 1;
      v4 += (v4 ^ (unsigned int)s[i]) % 0x539;
    }

	printf("Login: %s\nSerial: %u\n", s, v4);

    return 0;
}