/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:50:35 by hsamir            #+#    #+#             */
/*   Updated: 2025/01/28 16:36:04 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	printf("%d\n", argc);
	if (argc != 5 && argc != 6)
		return (printf(ARGUMENT_ERROR));
	t_sim_config s = parse_arguments(argc,argv);
	printf("<philos:%d> <t_die:%d> <t_eat:%d> <t_sleep:%d> [eat_count:%d], err check:%d\n", s.philo_count,s.die_time_ms,s.eat_time_ms,s.sleep_time_ms,s.max_meals,s.err);
}
