/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:39:49 by hsamir            #+#    #+#             */
/*   Updated: 2025/02/05 12:56:08 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../../../includes/philo.h"

void	sync_printf(char *message, t_philosopher *p)
{
	pthread_mutex_lock(p->sim->write_lock);
	if (get_sim_state(p->sim) == RUNNING)
		printf(message, get_time_diff(p->sim->start_time), p->id);
	pthread_mutex_unlock(p->sim->write_lock);
}