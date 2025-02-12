/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_monitor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:51:40 by hsamir            #+#    #+#             */
/*   Updated: 2025/02/12 22:11:37 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/philo.h"
#include <stdio.h>

int	is_philo_starved(t_philosopher *philo)
{
	return (current_time_ms() >= (philo->sim->die_time_ms
			+ get_last_meal_time(philo)));
}

int	check_philo(t_philosopher *philo)
{
	if (is_philo_starved(philo))
	{
		set_sim_state(philo->sim, TERMINATED);
		printf("%ld %d died\n", (current_time_ms() - philo->sim->start_time),
			philo->id);
		return (1);
	}
	return (0);
}

int	check_all_philos_full(int full_philo_count, t_simulation *sim)
{
	if (sim->max_meals > 0 && full_philo_count == sim->philo_count)
	{
		set_sim_state(sim, TERMINATED);
		return (1);
	}
	return (0);
}

void	*monitor_thread(void *arg)
{
	t_simulation	*sim;
	int				full_philo_count;
	int				i;

	sim = (t_simulation *)arg;
	set_sim_state(sim, RUNNING);
	sim->start_time = current_time_ms();
	i = 0;
	while (get_sim_state(sim) == RUNNING)
	{
		full_philo_count = 0;
		while (sim->philos[i])
		{
			if (check_philo(sim->philos[i]))
				break ;
			if (get_eat_count(sim->philos[i]) >= sim->max_meals)
				full_philo_count++;
			i++;
		}
		if (check_all_philos_full(full_philo_count, sim))
			break ;
		i = 0;
	}
	return (NULL);
}
