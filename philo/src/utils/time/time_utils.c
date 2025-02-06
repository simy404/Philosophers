/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:21:16 by hsamir            #+#    #+#             */
/*   Updated: 2025/02/06 17:55:19 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>

long long current_time_ms() {
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000LL + tv.tv_usec / 1000;
}

unsigned long long	current_time_us() {
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000LL + tv.tv_usec;
}


void	msleep(unsigned long long time)
{
	unsigned long long start_time;
	
  	start_time = current_time_ms();
	// usleep((time * 1000 - 5000));
	while (current_time_ms() - start_time < time)
		usleep(100);
}

long long get_time_diff(long long start_time)
{
	return current_time_ms() - start_time;
}
