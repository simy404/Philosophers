/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_monitor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:51:40 by hsamir            #+#    #+#             */
/*   Updated: 2025/02/05 14:54:49 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/philo.h"

int	philo_die_check(t_philosopher *philo)
{
	if (get_sim_state(philo->sim) == TERMINATED)
		return (0);
	if (current_time_ms() - get_last_meal_time(philo) > philo->sim->die_time_ms)
		return (1);
	return (0);
}

void    *monitor_thread(void* arg)
{
	t_simulation    *sim;
	int i;
	
	sim = (t_simulation *)arg;
	i = 0;
	while (get_sim_state(sim) == RUNNING)
	{
		while (get_sim_state(sim) == RUNNING && sim->philos[i])
		{
			if (philo_die_check(sim->philos[i]))
			{
				sync_printf("%lld %d died\n", sim->philos[i]);
				set_sim_state(sim, TERMINATED);
				break ;
			}
			i++;
		}
		i = 0;
		msleep(10);
	}
	return (NULL);
}