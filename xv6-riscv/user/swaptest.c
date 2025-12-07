#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {

    printf("\nInitial memory state:\n");
    pgstat();

    char *pages[80];
    int allocated = 0;

    for (int i = 0; i < 80; i++) {
        pages[i] = sbrk(4096);
        if (pages[i] == (char*) -1) {
            break;
        }
        for (int j = 0; j < 4096; j += 512) {
            pages[i][j] = (char)(i & 0xFF);
        }
        allocated++;
    }

    pgstat();

    for (int i = allocated - 1; i >= 0; i--) {
        char val = pages[i][0];
        pages[i][0] = val + 1;
        pages[i][2048] = (char)(i & 0xFF);

    }

    printf("\n=== Test completed ===\n");
    pgstat();

    exit(0);
}
