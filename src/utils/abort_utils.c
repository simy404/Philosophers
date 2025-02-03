/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abort_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:02:46 by hsamir            #+#    #+#             */
/*   Updated: 2025/02/03 08:22:56 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include <stdlib.h>

void	abort_cs(t_critical_section *cs)
{
	if (cs->mutex)
	{
		pthread_mutex_destroy(cs->mutex);
		free(cs->mutex);
		cs->mutex = NULL;
	}
	if (cs->data)
	{
		free(cs->data);
		cs->data = NULL;
	}
}

void	abort_philos(t_philosopher   **philos, int philo_count)
{
	int	i;

	i = 0;
	while (i < philo_count)
	{
		abort_cs(&philos[i]->eat_count);
		abort_cs(&philos[i]->last_meal_time);
		free(philos[i]);
		i++;
	}
	free(philos);
}

void	abort_forks(pthread_mutex_t *fork_mutexes, int fork_count)
{
	int	i;

	i = 0;
	while (i < fork_count)
	{
		pthread_mutex_destroy(fork_mutexes + i);
		i++;
	}
	free(fork_mutexes);
}

void abort_simulation(t_simulation *simulation)
{
	if (!simulation)
		return ;
	if (simulation->philos)
		abort_philos(simulation->philos, simulation->philo_count);
	if (simulation->fork_mutexes)
		abort_forks(simulation->fork_mutexes, simulation->philo_count);
	abort_cs(&simulation->status);
	free(simulation);
}
