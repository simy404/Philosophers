/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   critical_section_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:50:38 by hsamir            #+#    #+#             */
/*   Updated: 2025/02/03 10:43:16 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include <stdlib.h>

#include <stddef.h>

void *ft_memcpy(void *dest, const void *src, size_t n)
{
    size_t i;
    unsigned char *d;
    unsigned char *s;

    if (!dest && !src)
        return (0);
    d = (unsigned char *)dest;
    s = (unsigned char *)src;
    i = 0;
    while (i < n)
    {
        d[i] = s[i];
        i++;
    }
    return (dest);
}

pthread_mutex_t	*create_mutex()
{
    pthread_mutex_t	*mutex;

    mutex = malloc(sizeof(pthread_mutex_t));
    if (!mutex)
        return (NULL);
    if (pthread_mutex_init(mutex, NULL))
    {
        free(mutex);
        return (NULL);
    }
    return (mutex);
}

int	init_cs(t_critical_section *cs, int size)
{
    cs->data = malloc(size);
    if (!cs->data)
        return (FAILURE);
    cs->mutex = create_mutex();
    if (!cs->mutex)
    {
        abort_cs(cs);
        return (FAILURE);
    }
    return (SUCCESS);
}

int	read_cs_data(t_critical_section *cs, void *data, int size)
{
    if (pthread_mutex_lock(cs->mutex))
        return (FAILURE);
    ft_memcpy(data, cs->data, sizeof(size));
    if (pthread_mutex_unlock(cs->mutex))
        return (FAILURE);
    return (SUCCESS);
}

int	write_cs_data(t_critical_section *cs, void *data, int size)
{
    if (pthread_mutex_lock(cs->mutex))
        return (FAILURE);
    ft_memcpy(cs->data, data, sizeof(size));
    if (pthread_mutex_unlock(cs->mutex))
        return (FAILURE);
    return (SUCCESS);
}
