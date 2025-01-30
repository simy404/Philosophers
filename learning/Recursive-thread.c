#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;
pthread_mutexattr_t attr;

void* thread_function(void* arg) {
    printf("Thread başladı...\n");

    printf("Mutex'i 1. kez kilitliyorum...\n");
    pthread_mutex_lock(&mutex);

    printf("Mutex'i 2. kez kilitliyorum...\n");
    pthread_mutex_lock(&mutex);  // Bu kez çalışacak çünkü recursive mutex!

    printf("İşlem başarılı! Deadlock olmadı!\n");

    pthread_mutex_unlock(&mutex);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    pthread_t thread;
    
    // Recursive mutex oluşturuyoruz
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
    pthread_mutex_init(&mutex, &attr);
    
    pthread_create(&thread, NULL, thread_function, NULL);
    pthread_join(thread, NULL);

    pthread_mutex_destroy(&mutex);
    return 0;
}
