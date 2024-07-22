/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:54:05 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/22 17:56:28 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

suseconds_t	ft_time_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}



void	ft_philo_born(t_philo *philo, t_env *env)
{
	int	i;

	i = 0;
	pthread_mutex_init(&env->life, NULL);
	while (i < env->argc)
	{
		usleep(200);
		philo[i].id = i;
		philo[i].life = env->life;
		philo[i].last_eat = ft_time_now();
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

void ft_message(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->life);
	printf(" %ld Philosophers %d %s\n",(long )philo->last_eat, philo->id, msg);
	pthread_mutex_unlock(&philo->life);
}
