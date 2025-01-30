#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main() {
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);  // Başlangıç zamanı

    usleep(500000);  // 500ms bekle

    clock_gettime(CLOCK_MONOTONIC, &end);  // Bitiş zamanı

    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1.0e9;

    printf("Gerçek bekleme süresi: %.6f saniye\n", elapsed);

    return 0;
}
