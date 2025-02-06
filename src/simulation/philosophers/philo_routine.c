/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:07:58 by hsamir            #+#    #+#             */
/*   Updated: 2025/02/06 09:52:20 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/philo.h"
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int philo_eat(t_philosopher* p)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	first = &p->sim->fork_mutexes[(p->id - (p->id % 2)) % p->sim->philo_count];
	second = &p->sim->fork_mutexes[(p->id - !(p->id % 2)) % p->sim->philo_count];
	pthread_mutex_lock(first);
	sync_printf("%lld %d has taken a fork\n", p);
	if (first == second)
	{
		msleep(p->sim->die_time_ms - (current_time_ms() - p->sim->start_time));
		pthread_mutex_unlock(first);
		return (FAILURE);
	};
	pthread_mutex_lock(second);
	if (get_sim_state(p->sim) == RUNNING)
	{
		sync_printf("%lld %d has taken a fork\n", p);
		sync_printf("%lld %d is eating\n", p);
		increase_eat_count(p);
		set_last_meal_time(p, current_time_ms());
		msleep(p->sim->eat_time_ms);
	}
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);
	return (SUCCESS);
}

int philo_sleep(t_philosopher *philo)
{
	sync_printf("%lld %d is sleeping\n", philo);
	msleep(philo->sim->sleep_time_ms);
	return 0;
}

int philo_think(t_philosopher *philo)
{
	int sleep_time;
	sync_printf("%lld %d is thinking\n", philo);
	
	sleep_time = philo->sim->think_time_ms;
	if (sleep_time > 0)
		msleep(sleep_time);
	else
		usleep(100); // I have to check that might be that's not necessary
	return 0;
}

void    *philo_routine(void* arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher*)arg;
	while (get_sim_state(philo->sim) == IDLE)
		;
	if (philo->id % 2)
		msleep(1);
	while (get_sim_state(philo->sim) == RUNNING)
	{
		if (!philo_eat(philo))
			break;
		if (get_sim_state(philo->sim) == TERMINATED)
			break;
		philo_sleep(philo);
		if (get_sim_state(philo->sim) == TERMINATED)
			break;
		philo_think(philo);
	}
	return (NULL);
}
