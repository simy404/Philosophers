/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_monitor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:51:40 by hsamir            #+#    #+#             */
/*   Updated: 2025/02/07 18:24:03 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/philo.h"
#include <unistd.h>
#include <stdio.h>

int	is_philo_die(t_philosopher *philo)
{
	if ((current_time_ms() - get_last_meal_time(philo)) > philo->sim->die_time_ms)
		return (1);
	return (0);
}

void    *monitor_thread(void* arg)
{
	t_simulation    *sim;
	int i;
	
	sim = (t_simulation *)arg;
	i = 0;
	while (get_sim_state(sim) == IDLE)
		;
	while (get_sim_state(sim) == RUNNING)
	{
		while (sim->philos[i])
		{
			if (is_philo_die(sim->philos[i]))
			{
				sync_printf("%lld %d died\n", sim->philos[i]);
				set_sim_state(sim, TERMINATED);
				break ;
			}
			i++;
		}
		i = 0;
	usleep(100);
	}
	return (NULL);
}