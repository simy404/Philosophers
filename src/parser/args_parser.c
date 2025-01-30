/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:14:21 by hsamir            #+#    #+#             */
/*   Updated: 2025/01/30 14:11:41 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	parse_uint(char *str, int *err)
{
	long	number;

	if (!is_valid_unumber(str))
	{
		*err = 1;
		return (0);
	}
	number = strtoui(str, err);
	if (*err)
		return (0);
	return (number);
}

t_sim_config	parse_arguments(int argc, char **argv)
{
	t_sim_config	config;

	config.max_meals = -1;
	config.err = 0;
	config.max_meals = -1;
	config.philo_count = parse_uint(argv[1], &config.err);
	config.die_time_ms = parse_uint(argv[2], &config.err);
	config.eat_time_ms = parse_uint(argv[3], &config.err);
	config.sleep_time_ms = parse_uint(argv[4], &config.err);
	if (argc == 6)
		config.max_meals = parse_uint(argv[5], &config.err);
	return (config);
}
