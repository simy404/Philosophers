/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_philosophers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:45:32 by hsamir            #+#    #+#             */
/*   Updated: 2025/02/03 11:07:27 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

long long current_time_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000LL + tv.tv_usec / 1000; // Milisaniye cinsine çevir
}

void    *philo_routine(void* arg)
{
    t_philosopher   *philo;
	int status;

	status = IDLE;
    philo = (t_philosopher*)arg;

    while (read_cs_data(&philo->sim->status, &status, sizeof(int)) && status == IDLE)
        ;
	// while (*((int*)philo->sim->status.data) == IDLE)
	// 	;
    printf("Philosopher %d is running - current time %lld\n", philo->id, current_time_ms());
    return (NULL);
}


t_philosopher   *initialize_philo(int id, t_simulation *simulation)
{
    t_philosopher   *philo;

    philo = malloc(sizeof(t_philosopher));
    if (!philo)
        return (NULL);
    philo->id = id;
    philo->sim = simulation;
    if (pthread_create(&philo->thread, NULL, philo_routine, philo))
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

    philos = malloc(sizeof(t_philosopher*) * (simulation->philo_count + 1));
    if (!philos)
        return (NULL);
    i = 0;
    while(i < simulation->philo_count)
    {
        philos[i] = initialize_philo(i + 1, simulation);
        if (!philos[i])
            return (abort_philos(philos, i), NULL);
        i++;
    }
    philos[i] = NULL;
    return (philos);
}
