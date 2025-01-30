/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   critical_section_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:50:38 by hsamir            #+#    #+#             */
/*   Updated: 2025/01/29 19:59:50 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

t_critical_section *create_cs(int data, int size)
{
    t_critical_section *cs;

    cs = malloc(sizeof(t_critical_section));
    if(!cs)
        return (NULL);
    cs->data = data;
    if (pthread_mutex_init(cs->mutex, NULL));
        return (free(cs)); //TODO I have to make safe free for that
    return (cs);
}

int get_cs(t_critical_section *cs)
{
    pthread_mutex_lock(cs->mutex);
        
    pthread_mutex_unlock(cs->mutex);
}



int set_cs()
{
    
}