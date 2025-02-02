/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:50:35 by hsamir            #+#    #+#             */
/*   Updated: 2025/02/02 14:10:52 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	// t_simulation *simulation;
	t_sim_config config;

	if (argc != 5 && argc != 6)
		return (printf(ARGUMENT_ERROR));
	config = parse_arguments(argc,argv);
	if (config.err)
		return (printf(ARGUMENT_ERROR));
	// simulation = initialize_simulation(config);
	t_critical_section cs;
	if (create_cs(&cs, sizeof(int)) == FAILURE)
	{
		printf("Critical section creation failed\n");
		return (1);
	}
	abort_cs(&cs);
	printf("<philos:%d> <t_die:%d> <t_eat:%d> <t_sleep:%d> [eat_count:%d], err check:%d\n", config.philo_count,config.die_time_ms,config.eat_time_ms,config.sleep_time_ms,config.max_meals,config.err);
}
