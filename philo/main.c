/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:50:35 by hsamir            #+#    #+#             */
/*   Updated: 2025/02/12 23:16:24 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_simulation	*simulation;
	t_sim_config	config;

	if (argc != 5 && argc != 6)
		return (printf(ARG_ERR));
	config = parse_arguments(argc, argv);
	if (config.err || config.philo_count < 1 || config.max_meals == 0)
		return (printf(ARG_ERR));
	simulation = initialize_simulation(config);
	if (!simulation)
		return (printf("Error: Simulation initialization failed\n"));
	if (!start_simulation(simulation))
		printf("Error: Simulation failed\n");
	abort_simulation(simulation);
}
