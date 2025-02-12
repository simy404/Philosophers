/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_metrics_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:44:46 by hsamir            #+#    #+#             */
/*   Updated: 2025/02/12 21:51:02 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/philo.h"

void	increase_eat_count(t_philosopher *philo)
{
	int	count;

	read_cs_data(&philo->eat_count, &count, sizeof(int));
	if (count < 0)
		return ;
	count++;
	write_cs_data(&philo->eat_count, &count, sizeof(int));
}

void	set_last_meal_time(t_philosopher *philo, unsigned long time)
{
	write_cs_data(&philo->last_meal_time, &time, sizeof(unsigned long));
}

unsigned long	get_last_meal_time(t_philosopher *philo)
{
	unsigned long	time;

	read_cs_data(&philo->last_meal_time, &time, sizeof(unsigned long));
	return (time);
}

int	get_eat_count(t_philosopher *philo)
{
	int	count;

	read_cs_data(&philo->eat_count, &count, sizeof(int));
	return (count);
}
