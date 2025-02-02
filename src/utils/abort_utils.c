/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abort_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:02:46 by hsamir            #+#    #+#             */
/*   Updated: 2025/02/02 17:44:15 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include <stdlib.h>

void	abort_cs(t_critical_section *cs)
{
    if (cs->mutex)
    {
        pthread_mutex_destroy(cs->mutex);
        free(cs->mutex);
        cs->mutex = NULL;
    }
    if (cs->data)
    {
        free(cs->data);
        cs->data = NULL;
    }
}

void abort_philos(t_philosopher   **philos, int philo_count)
{
    int i;

    i = 0;
    while (i < philo_count)
    {
        abort_cs(&philos[i]->eat_count);
        abort_cs(&philos[i]->last_meal_time);
        free(philos[i]);
        i++;
    }
    free(philos);
}
