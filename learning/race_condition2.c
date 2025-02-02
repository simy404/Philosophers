#include <stdio.h>
#include <pthread.h>

typedef struct race_condition2
{
	int miktar;
	pthread_mutex_t *mutex;
} racec; ;

int bakiye = 100;

void* increase_with_mutex(void* rc) {
	printf("Thread started\n");
	int artirilan_miktar = ((racec*)rc)->miktar;
	for (int i = 0; i < 5; i++)
	{
			printf("Thread %d\n", i);
			pthread_mutex_lock(((racec*)rc)->mutex);
			printf("locked\n");
			bakiye += artirilan_miktar;
			pthread_mutex_unlock(((racec*)rc)->mutex);
			printf("unlocked\n");
	}
	return NULL;
}

int main ()
{
	racec rc;
	pthread_mutex_t mutex;

	rc.mutex = &mutex;
	rc.miktar = 1;
	pthread_t thread1, thread2;
	int miktar1 = 1, miktar2 = 2;

	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_destroy(&mutex);
	printf("Ana bakiye: %d TL\n", bakiye);
	pthread_create(&thread1, NULL, increase_with_mutex, &rc);
	pthread_create(&thread2, NULL, increase_with_mutex, &rc);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	// pthread_mutex_destroy(&mutex);

	printf("Son bakiye: %d TL\n", bakiye);

	return 0;
}
