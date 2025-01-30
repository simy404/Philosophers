#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;

void* thread_function(void* arg) {
    printf("Thread çalışıyor...\n");

    pthread_mutex_lock(&mutex);
    printf("Mutex kilitlendi (1. kez)\n");

    pthread_mutex_lock(&mutex);
    // Deadlock: Aynı thread tekrar aynı mutex'i kilitlemeye çalışıyor!
    pthread_mutex_unlock(&mutex);
    printf("Bu satır asla yazdırılmaz! (Deadlock oluştu!)\n");

    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    pthread_t thread;
    
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&thread, NULL, thread_function, NULL);
    pthread_join(thread, NULL);

    pthread_mutex_destroy(&mutex);
    return 0;
}
