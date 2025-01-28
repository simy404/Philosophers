/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation_util.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:10:26 by hsamir            #+#    #+#             */
/*   Updated: 2025/01/28 16:45:19 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_within_uint_range(long number)
{
	return (number >= 0 && number <= UINT_MAX);
}

int	get_if_valid(char *str, int *err)
{
	long	number;
    
	if (!is_valid_number(str))
		return (0);
	number = strtoui(str, &err);
	if (err)
		return (0);
	return (number);
}