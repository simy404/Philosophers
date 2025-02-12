/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:21:16 by hsamir            #+#    #+#             */
/*   Updated: 2025/02/12 21:38:26 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>

unsigned long	current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + (tv.tv_usec) / 1000);
}

long	current_time_us(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

struct timeval	get_cur_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time);
}

void	msleep(unsigned long ms)
{
	unsigned long	start;

	start = current_time_ms();
	while (current_time_ms() - start < ms)
		usleep(100);
}
