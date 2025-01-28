/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:39:49 by hsamir            #+#    #+#             */
/*   Updated: 2025/01/28 12:42:18 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*print_error_null(char *error)
{
	ft_putendl_fd(error, 1);
	return (NULL);
}

void	*free_with_error_null(char *error, void *ptr)
{
	free(ptr);
	return (print_error_null(error));
}