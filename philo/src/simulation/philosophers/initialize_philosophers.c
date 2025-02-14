/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_philosophers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:45:32 by hsamir            #+#    #+#             */
/*   Updated: 2025/02/12 21:44:44 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/philo.h"
#include <stdlib.h>

t_philosopher	*initialize_philo(int id, t_simulation *simulation)
{
	t_philosopher	*philo;

	philo = malloc(sizeof(t_philosopher));
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->sim = simulation;
	if (pthread_create(&philo->thread, NULL, philo_routine, philo))
	{
		free(philo);
		return (NULL);
	}
	if (!init_cs(&philo->eat_count, sizeof(int)))
	{
		free(philo);
		return (NULL);
	}
	if (!init_cs(&philo->last_meal_time, sizeof(unsigned long)))
	{
		abort_cs(&philo->eat_count);
		free(philo);
		return (NULL);
	}
	set_last_meal_time(philo, current_time_ms());
	return (philo);
}

t_philosopher	**initialize_philos(t_simulation *simulation)
{
	t_philosopher	**philos;
	int				i;

	philos = malloc(sizeof(t_philosopher *) * (simulation->philo_count + 1));
	if (!philos)
		return (NULL);
	i = 0;
	while (i < simulation->philo_count)
	{
		philos[i] = initialize_philo(i + 1, simulation);
		if (!philos[i])
			return (abort_philos(philos, i), NULL);
		i++;
	}
	philos[i] = NULL;
	return (philos);
}
