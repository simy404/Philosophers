#include <stdio.h>
#include <pthread.h>

int bakiye = 100;

void* para_cek(void* miktar) {
    int cekilen_miktar = *(int*)miktar; // 100  || 100
    if (bakiye >= cekilen_miktar) {
        // Bakiye kontrolü yapıldı, ancak burada bir race condition oluşabilir
        printf("%d TL çekiliyor...\n", cekilen_miktar);
        bakiye -= cekilen_miktar;
        printf("Yeni bakiye: %d TL\n", bakiye);
    } else {
        printf("Yetersiz bakiye! %d TL çekilemedi.\n", cekilen_miktar);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    int miktar1 = 50, miktar2 = 100;

    // İki thread oluşturuluyor
    pthread_create(&thread1, NULL, para_cek, &miktar1);
    pthread_create(&thread2, NULL, para_cek, &miktar2);

    // Thread'lerin bitmesini bekliyoruz
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Son bakiye: %d TL\n", bakiye);

    return 0;
}
