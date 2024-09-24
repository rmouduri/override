Dans les sources:

printf("Password:");
  scanf("%d", &v4);
  if ( v4 == 5276 )
  {
    puts("\nAuthenticated!");
    system("/bin/sh");
    return 0;
  }

# bash:
	> ./level00
<<< Password:
	> 5276
	> cat /home/users/level01/.pass
<<< uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL