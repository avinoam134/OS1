#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    set_affinity_mask(1 | 1 << 2);
    printf("AFTER CHANGING AFFINITY\n");
    for (int i = 0; i < 100; i++)
    {
        printf("Process ID: %d\n", getpid());
    }
    exit(0, "Goodbye!\n");
}