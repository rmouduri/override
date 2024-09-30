int decrypt(char a1)
{
  char encrypted_string[29];

  *(_DWORD *)&encrypted_string[17] = __readgsdword(0x14u);
  strcpy(encrypted_string, "Q}|u`sfg~sf{}|a3");
  for (unsigned int i = 0; i < strlen(encrypted_string); ++i )
    encrypted_string[i] ^= a1;
  if ( !strcmp(encrypted_string, "Congratulations!") )
    return system("/bin/sh");
  else
    return puts("\nInvalid Password");
}

int  test(int a1, int a2)
{
  int result;

  switch ( a2 - a1 )
  {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
      result = decrypt(a2 - a1);
      break;
    default:
      result = decrypt(rand());
      break;
  }
  return result;
}

int  main(int argc, const char **argv, const char **envp)
{
  int input;

  srand(time(0));
  puts("***********************************");
  puts("*\t\tlevel03\t\t**");
  puts("***********************************");
  printf("Password:");
  __isoc99_scanf("%d", &input);
  test(input, 322424845);
  return 0;
}