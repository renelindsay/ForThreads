#include <stdio.h>
#include "for_threads.h"

int main() {
    printf("Optimal thread-count for this CPU: %d\n", ForThread.max_threads());

    for_threads(12) {
        printf("loop i=%d\n", i);
    };

    printf("done\n");
    return 0;
}
