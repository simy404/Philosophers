/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:07:58 by hsamir            #+#    #+#             */
/*   Updated: 2025/02/11 19:59:26 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/philo.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int	philo_eat(t_philosopher *p)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	// first = &p->sim->fork_mutexes[(p->id - (p->id % 2)) % p->sim->philo_count];
	// second = &p->sim->fork_mutexes[(p->id - !(p->id % 2)) % p->sim->philo_count];
	if (p->id % 2)
	{
		first = &p->sim->fork_mutexes[p->id % p->sim->philo_count];
		second = &p->sim->fork_mutexes[(p->id - 1) % p->sim->philo_count];
	}
	else
	{
		first = &p->sim->fork_mutexes[(p->id - 1) % p->sim->philo_count];
		second = &p->sim->fork_mutexes[p->id % p->sim->philo_count];
	}
	// first = &p->sim->fork_mutexes[(p->id - !(p->id == (unsigned int)p->sim->philo_count))
	// 	% p->sim->philo_count]; // 1 - 1
	// second = &p->sim->fork_mutexes[(p->id - (p->id == (unsigned int)p->sim->philo_count))
	// 	% p->sim->philo_count];


	// first = &p->sim->fork_mutexes[(p->id - 1) % p->sim->philo_count];
	// second = &p->sim->fork_mutexes[(p->id) % p->sim->philo_count];
	pthread_mutex_lock(first);
	sync_printf("%lld %d has taken a fork\n", p);
	if (first == second) // im gonna check that
	{
		msleep(p->sim->die_time_ms - (current_time_ms() - p->sim->start_time));
		pthread_mutex_unlock(first);
		return (FAILURE);
	}
	pthread_mutex_lock(second);
	if (get_sim_state(p->sim) == RUNNING)
	{
		sync_printf("%lld %d has taken a fork\n", p);
		sync_printf("%lld %d is eating\n", p);
		set_last_meal_time(p, current_time_ms());
		increase_eat_count(p);
		msleep(p->sim->eat_time_ms);
	}
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);
	return (SUCCESS);
}

int	philo_sleep(t_philosopher *philo)
{
	sync_printf("%lld %d is sleeping\n", philo);
	msleep(philo->sim->sleep_time_ms);
	return (0);
}

int	philo_think(t_philosopher *philo)
{
	int sleep_time;
	sync_printf("%lld %d is thinking\n", philo);
	sleep_time = philo->sim->think_time_ms;
	if (sleep_time > 0)
		msleep(sleep_time);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (get_sim_state(philo->sim) == IDLE)
		;
	set_last_meal_time(philo, current_time_ms());
	if (philo->id % 2)
		msleep(1);
	while (get_sim_state(philo->sim) == RUNNING)
	{
		if (!philo_eat(philo))
			break ;
		if (get_sim_state(philo->sim) == TERMINATED)
			break ;
		philo_sleep(philo);
		if (get_sim_state(philo->sim) == TERMINATED)
			break ;
		philo_think(philo);
	}
	return (NULL);
}
