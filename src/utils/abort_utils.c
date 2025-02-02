/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abort_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:02:46 by hsamir            #+#    #+#             */
/*   Updated: 2025/02/02 17:03:42 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include <stdlib.h>

void	abort_cs(t_critical_section *cs)
{
    if (cs->mutex)
    {
        pthread_mutex_destroy(cs->mutex);
        free(cs->mutex);
        cs->mutex = NULL;
    }
    if (cs->data)
    {
        free(cs->data);
        cs->data = NULL;
    }
}
