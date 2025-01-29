/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_simulation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:24:18 by hsamir            #+#    #+#             */
/*   Updated: 2025/01/29 11:23:18 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

t_philosopher *initialize_philosophers(int id, t_simulation *simulation)
{
    t_philosopher *philo = malloc(sizeof(t_philosopher));
    if (!philo)
        return (NULL);
    philo->t_sim = simulation;
    philo->eat_count;
    philo->id = id;
    philo->last_meal_time;
    philo->thread;
}

t_simulation *initialize_simulation(t_sim_config config)
{
    t_simulation *simulation;
    int i;
    
    simulation = malloc(sizeof(t_simulation));
    if (!simulation)
        return (NULL);
    simulation->philo_count = config.philo_count;
    simulation->die_time_ms = config.die_time_ms;
    simulation->eat_time_ms = config.eat_time_ms;
    simulation->sleep_time_ms = config.sleep_time_ms;
    simulation->max_meals = config.max_meals;
    simulation->status = IDLE;
    simulation->philos = malloc(sizeof(t_philosopher) * config.philo_count);
    if (!simulation->philos)
        return (free(simulation), NULL);
    simulation->fork_mutexes = malloc(sizeof(pthread_mutex_t) * config.philo_count);
    if (!simulation->fork_mutexes)
        return (free(simulation->philos), free(simulation), NULL);
    i = 0;
    while (i < config.philo_count)
    {
        simulation->philos[i] = initialize_philosophers(i++, simulation);
    if (!simulation->philos[i])
        (void*)(config)//safe free;
    }   
    
}