/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:07:58 by hsamir            #+#    #+#             */
/*   Updated: 2025/02/03 13:17:49 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include <sys/time.h>

int philo_eat(t_philosopher* philo);
{
	return 0;
}

int philo_sleep()
{
	return 0;
}

int philo_think()
{
	return 0;
}

long long current_time_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000LL + tv.tv_usec / 1000; // Milisaniye cinsine çevir
}

void    *philo_routine(void* arg)
{
    t_philosopher   *philo;
	int status;

	status = IDLE;
    philo = (t_philosopher*)arg;

    while (read_cs_data(&philo->sim->status, &status, sizeof(int)) && status == IDLE)
        ;
	// while (*((int*)philo->sim->status.data) == IDLE)
	// 	;
    printf("Philosopher %d is running - current time %lld\n", philo->id, current_time_ms());
    return (NULL);
}
