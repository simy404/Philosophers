/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_simulation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:24:18 by hsamir            #+#    #+#             */
/*   Updated: 2025/02/02 17:40:48 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void* philo_routine(void*);

t_philosopher   *initialize_philo(int id, t_simulation *simulation)
{
    t_philosopher   *philo;

    philo = malloc(sizeof(t_philosopher));
    if (!philo)
        return (NULL);
    philo->id = id;
    philo->t_sim = simulation;
    if (!pthread_create(&philo->thread, NULL, philo_routine, philo))
            return (free(philo), NULL);
    if (!init_cs(&philo->eat_count, sizeof(int)))
        return (free(philo), NULL);
    if (!init_cs(&philo->last_meal_time, sizeof(int)))
        return (abort_cs(&philo->eat_count), free(philo), NULL);
    return (philo);
}


t_philosopher   **initialize_philos(t_simulation *simulation)
{
    t_philosopher   **philos;
    int              i;

    philos = malloc(sizeof(t_philosopher*) * simulation->philo_count + 1);
    if (!philos)
        return (NULL);
    i = 0;
    while(i < simulation->philo_count)
        philos[i] = initialize_philo(i + 1, simulation);
    philos[i] = NULL;
    return (philos);
}

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
    simulation->status = IDLE;
    simulation->fork_mutexes = initialize_forks(simulation->philo_count);
    if (!simulation->fork_mutexes)
        return (free(simulation), NULL);
    simulation->philos = initialize_philos(simulation->philo_count);
    if (!simulation->philos)
        return (free(simulation->fork_mutexes),free(simulation), NULL);
   return (simulation);
}
