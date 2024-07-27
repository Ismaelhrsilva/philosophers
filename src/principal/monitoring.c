/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 15:00:23 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/27 16:12:29 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_monitoring(void *arg)
{
	t_monitor	*monitor;
	int			last_eat;
	int			time_die;
	int			i;

	monitor = (t_monitor *)arg;
	i = 0;
	while (1)
	{
		usleep(10 * 1000);
		if (i == monitor->env->n_philo)
			i = 0;
		last_eat = ft_time_now() - monitor->philo[i].last_eat;
		time_die = monitor->env->time_die;
		if (last_eat > time_die)
		{
			if ((monitor->philo[i].n_eat) != monitor->env->n_eat)
				ft_message(&monitor->philo[i], "died",
					ft_time_now() - monitor->philo[i].born);
				monitor->env->started = 1;
			break ;
		}
		i++;
	}
	return (arg);
}
