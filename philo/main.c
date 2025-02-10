/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:50:35 by hsamir            #+#    #+#             */
/*   Updated: 2025/02/10 12:38:28 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_simulation	*simulation;
	t_sim_config	config;

	if (argc != 5 && argc != 6)
		return (printf(ARGUMENT_ERROR));
	config = parse_arguments(argc,argv);
	if (config.err)
		return (printf(ARGUMENT_ERROR));
	simulation = initialize_simulation(config);
	if (!simulation)
		return (printf("Error: Simulation initialization failed\n"));
	printf("<philos:%d> <t_die:%d> <t_eat:%d> <t_sleep:%d> [eat_count:%d], err check:%d\n", simulation->philo_count,config.die_time_ms,config.eat_time_ms,config.sleep_time_ms,config.max_meals,config.err);
	if (!start_simulation(simulation))
		printf("Error: Simulation failed\n");
	abort_simulation(simulation);
}
