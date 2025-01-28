/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convertion_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:07:05 by hsamir            #+#    #+#             */
/*   Updated: 2025/01/28 16:28:36 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	skip_whitespace(const char *c)
{
	int	i;

	i = 0;
	while ((c[i] == ' ' || (c[i] >= 9 && c[i] <= 13)))
		i++;
	return (i);
}

int	determine_sign(const char *c, int *i)
{
	int	sign;

	sign = 1;
	if ((c[*i] == '-' || c[*i] == '+'))
	{
		if (c[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

int	strtoui(const char *str, int *error)
{
	long	total;
	int		sign;
	int		i;

	total = 0;
	i = skip_whitespace(str);
	sign = determine_sign(str, &i);
	while ((str[i]) && (str[i] <= '9' && str[i] >= '0'))
	{
		total = total * 10 + str[i++] - '0';
		if (!is_within_uint_range(total * sign))
		{
			*error = 1;
			return (0);
		}
	}
	return (sign * total);
}