#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
unsigned long long current_time_ms() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000LL + tv.tv_usec;
}


void	ft_usleep(unsigned long time)
{
	unsigned long long start_time;

	start_time = current_time_ms();
    printf("start_time: %lld\n", start_time);
	usleep((time * 1000 - 10000));
	while (current_time_ms() - start_time < time * 1000)
		;
}
// struct timeval	get_cur_time(void)
// {
// 	struct timeval	current_time;

// 	gettimeofday(&current_time, NULL);
// 	return (current_time);
// }
// void	suspend_thread(struct timeval time)
// {
// 	struct timeval		start;
// 	unsigned long long	time_usec;
// 	unsigned long long	start_usec;
// 	unsigned long long	cur_usec;
// 	struct timeval		cur;

// 	time_usec = time.tv_sec * 1000000 + time.tv_usec;
// 	start = get_cur_time();
// 	start_usec = start.tv_sec * 1000000 + start.tv_usec;
// 	cur_usec = 0;
// 	usleep(time_usec - 10000);
// 	cur = get_cur_time();
// 	cur_usec = cur.tv_sec * 1000000 + cur.tv_usec;
// 	while (cur_usec - start_usec < time_usec)
// 	{
// 		cur = get_cur_time();
// 		cur_usec = cur.tv_sec * 1000000 + cur.tv_usec;
// 	}
// }

int main() {
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);  // Başlangıç zamanı
    // struct timeval time;
    // time.tv_sec = 0;
    // time.tv_usec = 500000;
    // suspend_thread(time);  // 500ms bekle
    ft_usleep(500);  // 500ms bekle
    // usleep(500000);  // 500ms bekle
    clock_gettime(CLOCK_MONOTONIC, &end);  // Bitiş zamanı

    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1.0e9;

    printf("Gerçek bekleme süresi: %.6f saniye\n", elapsed);

    return 0;
}
