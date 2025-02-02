/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_simulation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:24:18 by hsamir            #+#    #+#             */
/*   Updated: 2025/02/02 21:27:42 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include <stdlib.h>

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
    // simulation->fork_mutexes = initialize_forks(simulation->philo_count);
    // if (!simulation->fork_mutexes)
    //     return (free(simulation), NULL);
    simulation->philos = initialize_philos(simulation);
    if (!simulation->philos)
        return (free(simulation), NULL);
   return (simulation);
}
