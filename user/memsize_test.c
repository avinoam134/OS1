
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void memsize_test()
{
    int before_alloc_size = memsize();
    printf("Before extra memory allocation to the process: %d\n", before_alloc_size);
    void *obsolete = malloc(20000);
    int after_alloc_size = memsize();
    printf("After allocating 20K more bytes to the process: %d\n", after_alloc_size);
    free(obsolete);
    int after_realese = memsize();
    printf("After releasing the allocated memory: %d\n", after_realese);
}

int main(int argc, char *argv[])
{
    memsize_test();
    exit(0);
}
