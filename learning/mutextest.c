#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    pthread_mutex_t mutex;  // Mutex doğrudan struct içinde, stack'te olabilir!
    int *shared_data;
} t_critical_section;

t_critical_section cs;  // Stack üzerinde struct oluşturduk!
t_critical_section cs2;

void *thread_function(void *arg) {
    // t_critical_section *cs = (t_critical_section *)arg;

	for (size_t i = 0; i < 5; i++)
	{
		pthread_mutex_lock(&cs.mutex);
		printf("Thread %ld locked cs the mutex!\n", pthread_self());

		pthread_mutex_lock(&cs2.mutex);
		printf("Thread %ld locked the cs2 mutex!\n", pthread_self());


		(*cs.shared_data)++;
		i++;
		printf("Thread %ld incremented shared_data: %d\n", pthread_self(), *cs.shared_data);
		pthread_mutex_unlock(&cs.mutex);
		printf("Thread %ld unlocked cs the mutex!\n", pthread_self());
		pthread_mutex_unlock(&cs2.mutex);
		printf("Thread %ld unlocked cs2 the mutex!\n", pthread_self());
	}

    return NULL;
}

int main() {
    // Mutex'i başlat
    pthread_mutex_init(&cs.mutex, NULL);
    cs.shared_data = malloc(sizeof(int));
	*cs.shared_data = 0;
	cs2 = cs;
    pthread_t t1, t2;

    pthread_create(&t1, NULL, thread_function, &cs);
    // pthread_create(&t2, NULL, thread_function, &cs2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Mutex'i yok et
	pthread_mutex_destroy(&cs2.mutex);

    printf("Final shared_data: %d\n", *cs.shared_data);

    return 0;
}
