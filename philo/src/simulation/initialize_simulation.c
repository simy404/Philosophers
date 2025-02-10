/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_simulation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:24:18 by hsamir            #+#    #+#             */
/*   Updated: 2025/02/10 15:19:19 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>

int	start_simulation(t_simulation *simulation)
{
	int i;

	if (pthread_create(&simulation->monitor_thread, NULL, monitor_thread, simulation))
		return (FAILURE);
	i = 0;
	while (i < simulation->philo_count)
	{
		if (pthread_join(simulation->philos[i]->thread, NULL))
			return (FAILURE);
		i++;
	}
	if (pthread_join(simulation->monitor_thread, NULL))
		return (FAILURE);
	return (SUCCESS);
}

pthread_mutex_t* initialize_forks(int fork_count)
{
	pthread_mutex_t *fork_mutexes;
	int i;

	fork_mutexes = malloc(sizeof(pthread_mutex_t) * fork_count);
	if (!fork_mutexes)
		return (NULL);
	i = 0;
	while (i < fork_count)
	{
		if (pthread_mutex_init(fork_mutexes + i, NULL))
		{
			abort_forks(fork_mutexes, i);
			return (NULL);
		}
		i++;
	}
	return (fork_mutexes);
}

t_simulation    *initialize_simulation(t_sim_config config)
{
	t_simulation    *simulation;

	simulation = malloc(sizeof(t_simulation));
	if (!simulation)
		return (NULL);
	simulation->philo_count = config.philo_count;
	simulation->die_time_ms = config.die_time_ms;
	simulation->eat_time_ms = config.eat_time_ms;
	simulation->sleep_time_ms = config.sleep_time_ms;
	simulation->max_meals = config.max_meals;
	simulation->think_time_ms = (config.die_time_ms - (config.sleep_time_ms + config.eat_time_ms)) / 2;
	simulation->write_lock = create_mutex();
	if (!simulation->write_lock)
		return (abort_simulation(simulation));
	if (!init_cs(&simulation->status, sizeof(int)))
		return (abort_simulation(simulation));
	set_sim_state(simulation, IDLE);
	simulation->fork_mutexes = initialize_forks(simulation->philo_count);
	if (!simulation->fork_mutexes)
		return (abort_simulation(simulation));
	simulation->philos = initialize_philos(simulation);
	if (!simulation->philos)
		return (abort_simulation(simulation));
	return (simulation);
}
