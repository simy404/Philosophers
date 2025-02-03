/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:21:16 by hsamir            #+#    #+#             */
/*   Updated: 2025/02/03 18:30:36 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>

long long current_time_ms() {
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000LL + tv.tv_usec / 1000; // Milisaniye cinsine çevir
}


unsigned long long	current_time_us() {
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000LL + tv.tv_usec;
}


void	msleep(unsigned long long time)
{
	unsigned long long start_time;

	start_time = current_time_us();
	usleep((time * 1000 - 10000));
	while (current_time_us() - start_time < time * 1000)
		;
}
