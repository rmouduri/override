int get_unum()
{
  int v1; // [esp+1Ch] [ebp-Ch] BYREF

  v1 = 0;
  fflush(stdout);
  scanf("%u", &v1);
  clear_stdin();
  return v1;
}

int store_number(int data)
{
  unsigned int number;
  unsigned int index;

  printf(" Number: ");
  number = get_unum();
  printf(" Index: ");
  index = get_unum();
  if ( index == 3 * (index / 3) || (number >> 24) == 183 )
  {
    puts(" *** ERROR! ***");
    puts("   This index is reserved for wil!");
    puts(" *** ERROR! ***");
    return 1;
  }
  else
  {
    *(int *)(data + index * 4) = number;
    return 0;
  }
}

int read_number(int data)
{
  int index;

  printf(" Index: ");
  index = get_unum();
  printf(" Number at data[%u] is %u\n", index, (int *)(data + index * 4));
  return 0;
}

//----- (08048723) --------------------------------------------------------
int main(int argc, const char **argv, const char **envp)
{
  int data[100];
  int number;
  char s[4];

  number = 0;
  *s = 0;
  memset(data, 0, sizeof(data));
  while ( *argv )
  {
    memset((void *)*argv, 0, strlen(*argv));
    ++argv;
  }
  while ( *envp )
  {
    memset((void *)*envp, 0, strlen(*envp));
    ++envp;
  }
  puts(
    "----------------------------------------------------\n"
    "  Welcome to wil's crappy number storage service!   \n"
    "----------------------------------------------------\n"
    " Commands:                                          \n"
    "    store - store a number into the data storage    \n"
    "    read  - read a number from the data storage     \n"
    "    quit  - exit the program                        \n"
    "----------------------------------------------------\n"
    "   wil has reserved some storage :>                 \n"
    "----------------------------------------------------\n");
  while ( 1 )
  {
    printf("Input command: ");
    number = 1;
    fgets(s, 20, stdin);
    s[strlen(s) - 1] = 0;
    if ( !memcmp(s, "store", 5u) )
    {
      number = store_number(*data);
      goto LABEL_13;
    }
    if ( !memcmp(s, "read", 4u) )
    {
      number = read_number(*data);
      goto LABEL_13;
    }
    if ( !memcmp(s, "quit", 4u) )
      return 0;
LABEL_13:
    if ( number )
      printf(" Failed to do %s command\n", s);
    else
      printf(" Completed %s command successfully\n", s);
    *s = 0;
  }
}