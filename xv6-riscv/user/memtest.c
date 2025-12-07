#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int npages;

  if(argc != 2) {
    printf("Usage: %s <number_of_pages>\n", argv[0]);
    exit(1);
  }

  npages = atoi(argv[1]);
  printf("Allocating %d pages...\n", npages);
  char *base = sbrk(npages * 4096);

  //write something in each page
  for(int i = 0; i < npages; i++) {
    base[i * 4096] = i & 0xff;
  }

  sleep(30);

  for(int i = 0; i < npages; i++) {
    if(base[i * 4096] != (i & 0xff)) {
      printf("Page %d corrupted!\n", i);
      exit(1);
    }
  }


  printf("Exiting...\n");
  exit(0);
}
