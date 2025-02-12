/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_state_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:15:55 by hsamir            #+#    #+#             */
/*   Updated: 2025/02/12 21:47:21 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/philo.h"

int	get_sim_state(t_simulation *sim)
{
	int	state;

	read_cs_data(&sim->status, &state, sizeof(int));
	return (state);
}

void	set_sim_state(t_simulation *sim, int state)
{
	write_cs_data(&sim->status, &state, sizeof(int));
}
