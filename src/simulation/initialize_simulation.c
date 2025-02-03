/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_simulation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:24:18 by hsamir            #+#    #+#             */
/*   Updated: 2025/02/03 15:38:10 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include <stdlib.h>
#include <time.h>

int	start_simulation(t_simulation *simulation)
{
	int i;
	int status;

	simulation->start_time = current_time_ms();
	status = RUNNING;
	write_cs_data(&simulation->status, &status, sizeof(int));
	i = 0;
	while (i < simulation->philo_count)
	{
		if (pthread_join(simulation->philos[i]->thread, NULL))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

pthread_mutex_t* initialize_forks(int fork_count)
{
	pthread_mutex_t *fork_mutexes;
	int i;

	fork_mutexes = malloc(sizeof(pthread_mutex_t) * fork_count);
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
	if (!init_cs(&simulation->status, sizeof(int)))
		return (free(simulation), NULL);
	*(int *)(simulation->status.data) = IDLE;
	simulation->fork_mutexes = initialize_forks(simulation->philo_count);
	if (!simulation->fork_mutexes)
		return (free(simulation), NULL);
	simulation->philos = initialize_philos(simulation);
	if (!simulation->philos)
		return (abort_forks(simulation->fork_mutexes, simulation->philo_count), free(simulation), NULL);
   return (simulation);
}
