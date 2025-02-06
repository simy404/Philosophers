#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// 3 adet global mutex
pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m3 = PTHREAD_MUTEX_INITIALIZER;

void* thread1(void* arg)
{
    pthread_mutex_lock(&m1);
    usleep(1000);  // kısacık bir bekleme
    pthread_mutex_lock(&m2);
    // ... kritik bölüm ...
    pthread_mutex_unlock(&m2);
    pthread_mutex_unlock(&m1);
    return NULL;
}

void* thread2(void* arg)
{
    pthread_mutex_lock(&m2);
    usleep(1000);
    pthread_mutex_lock(&m3);
    // ... kritik bölüm ...
    pthread_mutex_unlock(&m3);
    pthread_mutex_unlock(&m2);
    return NULL;
}

void* thread3(void* arg)
{
    pthread_mutex_lock(&m3);
    usleep(1000);
    pthread_mutex_lock(&m1);
    // ... kritik bölüm ...
    pthread_mutex_unlock(&m1);
    pthread_mutex_unlock(&m3);
    return NULL;
}

int main(void)
{
    pthread_t t1, t2, t3;

    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);
    pthread_create(&t3, NULL, thread3, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    return 0;
}