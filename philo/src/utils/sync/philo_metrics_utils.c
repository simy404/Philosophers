/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_metrics_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:44:46 by hsamir            #+#    #+#             */
/*   Updated: 2025/02/06 09:10:32 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/philo.h"

void increase_eat_count(t_philosopher *philo)
{
    int count;
    
    read_cs_data(&philo->eat_count, &count, sizeof(int));
    if (count < 0)
        return ;
    count++;
    write_cs_data(&philo->eat_count, &count, sizeof(int));
}

void set_last_meal_time(t_philosopher *philo, long time)
{
    write_cs_data(&philo->last_meal_time, &time, sizeof(long long));
}

long long get_last_meal_time(t_philosopher *philo)
{
    long long time;
    
    read_cs_data(&philo->last_meal_time, &time, sizeof(long long));
    return (time);
}
