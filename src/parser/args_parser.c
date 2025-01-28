/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:14:21 by hsamir            #+#    #+#             */
/*   Updated: 2025/01/28 16:29:24 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

t_sim_config    parse_arguments(int argc, char** argv)
{
    t_sim_config config;
    
    config.err = 0;
    config.philo_count = strtoui(argv[1], &config.err);
    config.die_time_ms = strtoui(argv[2], &config.err); //TODO maybe, i might convert that from int to time
    config.eat_time_ms = strtoui(argv[3], &config.err);
    config.sleep_time_ms = strtoui(argv[4], &config.err);
    if (argc == 6)
        config.max_meals = strtoui(argv[5], &config.err);
    else
        config.max_meals = -1;
    return (config);
}