/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:07:58 by hsamir            #+#    #+#             */
/*   Updated: 2025/02/03 22:20:50 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int philo_eat(t_philosopher* philo)
{
	pthread_mutex_t *left;
	pthread_mutex_t *right;

	if (philo->id % 2)
	{
		left = &philo->sim->fork_mutexes[philo->id - 1];
		right = &philo->sim->fork_mutexes[philo->id % philo->sim->philo_count];
	}
	else
	{
		left = &philo->sim->fork_mutexes[philo->id % philo->sim->philo_count];
		right = &philo->sim->fork_mutexes[philo->id - 1];
	}
	if (left == right)
		return (FAILURE); //TODO philo count is 1;
	if (pthread_mutex_lock(left))
		return (FAILURE);
	printf("%lld %d has taken a fork\n", (current_time_ms() -  philo->sim->start_time) , philo->id);
	if (pthread_mutex_lock(right))
	{
		pthread_mutex_unlock(left);
		return (FAILURE);
	}
	printf("%lld %d has taken a fork\n", (current_time_ms() -  philo->sim->start_time) , philo->id);
	printf("%lld %d is eating\n", (current_time_ms() -  philo->sim->start_time) , philo->id);
	msleep(philo->sim->eat_time_ms);
	if (pthread_mutex_unlock(right))
		return (FAILURE);
	if (pthread_mutex_unlock(left))
		return (FAILURE);
	return (SUCCESS);
}

int philo_sleep(t_philosopher *philo)
{
	printf("%lld %d is sleeping\n", (current_time_ms() -  philo->sim->start_time) , philo->id);
	msleep(philo->sim->sleep_time_ms);
	return 0;
}

int philo_think(t_philosopher *philo)
{
	printf("%lld %d is thinking\n", (current_time_ms() -  philo->sim->start_time) , philo->id);
	msleep((philo->sim->die_time_ms - (philo->sim->sleep_time_ms + philo->sim->eat_time_ms ) / 2));
	return 0;
}

void    *philo_routine(void* arg)
{
	t_philosopher	*philo;
	int				status;

	status = IDLE;
	philo = (t_philosopher*)arg;
	while (read_cs_data(&philo->sim->status, &status, sizeof(int)) && status == IDLE)
		;
	if (philo->id % 2)
		usleep(1000);
	while (read_cs_data(&philo->sim->status, &status, sizeof(int)) && status == RUNNING)
	{
		philo_eat(philo);
		if (read_cs_data(&philo->sim->status, &status, sizeof(int)) && status == TERMINATED)
			break;
		philo_sleep(philo);
		if (read_cs_data(&philo->sim->status, &status, sizeof(int)) && status == TERMINATED)
			break;
		philo_think(philo);
	}
	printf("Philosopher %d is running - current time %lld\n", philo->id, current_time_ms());
	return (NULL);
}
