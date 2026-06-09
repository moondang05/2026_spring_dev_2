#include <stdio.h>

#include "add.h"

int main(void) {
    int x = 10;
    int y = 20;

    printf("%d + %d = %d\n", x, y, add(x, y));
    return 0;
}
