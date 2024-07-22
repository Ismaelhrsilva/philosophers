/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:54:05 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/22 19:07:10 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_philo_born(t_philo *philo, t_env *env)
{
	int	i;

	i = 0;
	pthread_mutex_init(&env->life, NULL);
	while (i < env->argc)
	{
		usleep(400);
		philo[i].id = i;
		philo[i].life = env->life;
		philo[i].last_eat = ft_time_now();
		philo[i].last_sleep = philo[i].last_eat;
		philo[i].last_thinking = philo[i].last_eat;
		i++;
	}
}

void	ft_philo_after_life(t_philo *philo, t_env *env)
{
	int	i;

	i = 0;
	(void )philo;
	pthread_mutex_destroy(&env->life);
	/*while (i < env->argc)
	{
		i++;
	}*/
}
