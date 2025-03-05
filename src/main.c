#include <stdio.h>
#include "malloc.h"

int main() {
    char *ptr = (char *)mallocx(1024);
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Memory allocated at %p\n", ptr);
    freex(ptr);
    printf("Memory freed\n");
    for (int i = 0; i < 1e10; i++) {
        ptr = (char *)mallocx(1UL << 31);
        freex(ptr);
    }

    return 0;
}
