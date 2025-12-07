#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define NUMPAGES 52
#define PGSIZE 4096

int main(int argc, char *argv[])
{
  char *pages[NUMPAGES];
  int i, pid;

  //allocate pages to trigger swapping
  for(i = 0; i < NUMPAGES; i++) {
    pages[i] = malloc(PGSIZE);
    if(pages[i] == 0) {
      printf("malloc failed on page %d\n", i);
      exit(1);
    }

    //writing some values to the page so that they stay in mem
    memset(pages[i], 0xAA + (i % 16), PGSIZE);
    *(int*)pages[i] = 0x12340000 + i;

  }

  //cpu burn
  for(int j = 0; j < 1000000; j++);

  //fork
  pid = fork();

  if(pid < 0) {
    printf("fork failed\n");
    exit(1);
  }

  if(pid == 0) {
    for(i = NUMPAGES - 1; i >= 0; i -= 5) {

      *(int*)pages[i] = 0xC0DE0000 + i;
    }
    printf("[CHILD] Finished accessing pages. Exiting...\n");
    exit(0);

  } else {

    printf("[PARENT] Finished accessing pages. Exiting...\n");

  }

  exit(0);
}
