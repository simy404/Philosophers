/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:21:16 by hsamir            #+#    #+#             */
/*   Updated: 2025/02/07 17:25:07 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>

long long current_time_ms() {
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000LL + tv.tv_usec / 1000;
}


long long get_time_diff(long long start_time)
{
	return current_time_ms() - start_time;
}

struct timeval	get_cur_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time);
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