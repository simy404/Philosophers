/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_monitor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:51:40 by hsamir            #+#    #+#             */
/*   Updated: 2025/02/10 14:49:35 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/philo.h"
#include <stdio.h>
#include <unistd.h>

int	has_philo_died(t_philosopher *philo)
{
	return (current_time_ms() >= (philo->sim->die_time_ms
			+ get_last_meal_time(philo)));
}
 
void	*monitor_thread(void *arg)
{
	t_simulation *sim;
	int full_philo_count;
	int i;

	sim = (t_simulation *)arg;
	set_sim_state(sim, RUNNING);
	sim->start_time = current_time_ms();
	i = 0;
	full_philo_count = 0;
	while (get_sim_state(sim) == RUNNING)
	{
		while (sim->philos[i])
		{
			if (has_philo_died(sim->philos[i]))
			{
				sync_printf("%lld %d died\n", sim->philos[i]);
				printf ("last meal time: %ld\n", get_last_meal_time(sim->philos[i]));
				set_sim_state(sim, TERMINATED);
				break ;
			}
			if (get_eat_count(sim->philos[i]) == sim->max_meals)
				full_philo_count++;
			i++;
		}
		if (sim->max_meals > 0  && full_philo_count == sim->philo_count)
		{
			set_sim_state(sim, TERMINATED);
			break ;
		}
		i = 0;
	}
	return (NULL);
}
