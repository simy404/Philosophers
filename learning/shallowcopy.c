#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
} ShallowStruct;

int main() {
    ShallowStruct original;
    original.data = malloc(sizeof(int));  // Heap'te bellek tahsis ettik.
    *original.data = 42;

    // SHALLOW COPY: Sadece pointerı kopyalıyoruz!
    ShallowStruct copy = original;

    printf("Original: %d\n", *original.data);
    printf("Copy: %d\n", *copy.data);

    // Değeri değiştirirsek, orijinal ve kopya aynı veriyi gösterdiği için etkilenir.
    *copy.data = 99;

    printf("After modification:\n");
    printf("Original: %d\n", *original.data);  // 99
    printf("Copy: %d\n", *copy.data);  // 99
	printf("Address of original: %p\n", &original);
	printf("Address of copy: %p\n", &copy);


    free(original.data);  // Heap belleği serbest bıraktık.

    // Burada copy.data artık geçersiz! Çünkü free() çağrısı heap belleği temizledi.
    // *copy.data = 77; // Tanımsız davranış (undefined behavior)!

    return 0;
}
