#include <sys/time.h>
#include <unistd.h>

struct timeval	get_cur_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time);
}

unsigned long long	tv_to_us(struct timeval tv)
{
	return (tv.tv_sec * 1e6 + tv.tv_usec);
}

void	msleep(long long time)
{
	struct timeval		start;
	unsigned long long	time_usec;
	unsigned long long	start_usec;
	unsigned long long	cur_usec;
	struct timeval		cur;

	time_usec = time * 1000;
	start = get_cur_time();
	start_usec = start.tv_sec * 1000000 + start.tv_usec;
	usleep(time_usec - 10000);
	cur = get_cur_time();
	cur_usec = cur.tv_sec * 1000000 + cur.tv_usec;
	while (cur_usec - start_usec < time_usec)
	{
		cur = get_cur_time();
		cur_usec = cur.tv_sec * 1000000 + cur.tv_usec;
	}
}

unsigned long	get_time_ms(struct timeval tv)
{
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

unsigned long	get_time_us()
{
	struct timeval tv;

	tv = get_cur_time();
	return (tv.tv_sec * 1e6 + tv.tv_usec);
}

unsigned long	get_current_time_ms(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (get_time_ms(now));
}

void	ft_sleep(unsigned long ms)
{
	unsigned long	start;

	// start = get_time_us();
	// while ((get_time_us() - start) < (ms * 1000llu))
	// 	usleep(285);

	start = get_current_time_ms() ;
	while (get_current_time_ms()  - start < ms)
		usleep(100);
}
