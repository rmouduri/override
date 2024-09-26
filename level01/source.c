#include <stdbool.h>

char a_user_name[100]; // idb

bool verify_user_name()
{
  puts("verifying username....\n");
  return memcmp(a_user_name, "dat_wil", 7) != 0;
}

bool verify_user_pass(const void *a1)
{
  return memcmp(a1, "admin", 5) != 0;
}

int main()
{
  char s[64];

  memset(s, 0, sizeof(s));
  puts("********* ADMIN LOGIN PROMPT *********");
  printf("Enter Username: ");
  fgets(a_user_name, 256, 0);
  if ( verify_user_name() )
  {
    puts("nope, incorrect username...\n");
  }
  else
  {
    puts("Enter Password: ");
    fgets(s, 100, 0);
    verify_user_pass(s);
    puts("nope, incorrect password...\n");
  }
  return 1;
}