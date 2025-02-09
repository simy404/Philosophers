#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>

#ifndef THREAD_COUNT
 #define THREAD_COUNT	100
#endif

#ifndef SLEEP_TIME
 #define SLEEP_TIME	100
#endif
void				msleep(long long time);
struct timeval		get_cur_time(void);
unsigned long long	tv_to_us(struct timeval tv);
void				ft_sleep(unsigned long ms);

unsigned long long	start_time;
pthread_mutex_t		lock_mutex;
int					lock = 1;

int	get_lock(void)
{
	int get_value;
	pthread_mutex_lock(&lock_mutex);
	get_value = lock;
	pthread_mutex_unlock(&lock_mutex);
	return get_value;
}

void set_lock(int new_value)
{
	pthread_mutex_lock(&lock_mutex);
	lock = new_value;
	pthread_mutex_unlock(&lock_mutex);
}

void	*routine(void *arg)
{
	int					id = *(int *)arg;
	unsigned long long	now;

	while (get_lock())
		;
	now = start_time;
	while (1)
	{
		printf("%d\t%llu\n", id, (now - start_time) / 1000);
		ft_sleep(SLEEP_TIME);
		now = tv_to_us(get_cur_time());
	}
}

int	main()
{
	pthread_t		thread[THREAD_COUNT];

	for (int i = 0; i < THREAD_COUNT; i++)
		pthread_create(&thread[i], NULL, routine, &i);
	start_time = tv_to_us(get_cur_time());
	set_lock(0);
	for (int i = 0; i < THREAD_COUNT; i++)
		pthread_join(thread[i], NULL);
}