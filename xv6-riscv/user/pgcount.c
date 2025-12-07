#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  printf("=== Page Statistics ===\n");
  pgstat();
  printf("========================\n");
  exit(0);
}
