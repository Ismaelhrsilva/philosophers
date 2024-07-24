/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:54:05 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/22 20:42:38 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_pmutex	*ft_create_mutex(t_env *env)
{
	int	i;
	t_pmutex	*fork;

	i = 0;
	fork = malloc(env->argc * sizeof(t_pmutex));
	while (i < env->argc)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
	return (fork);
}

void	ft_philo_born(t_philo *philo, t_env *env)
{
	int	i;
	t_pmutex	*fork;

	i = 0;
	pthread_mutex_init(&env->life, NULL);
	fork = ft_create_mutex(env);
	env->time_begin = ft_time_now();
	while (i < env->argc)
	{
		philo[i].id = i;
		philo[i].life = env->life;
		philo[i].born = env->time_begin;
		philo[i].last_eat = ft_time_now();
		philo[i].last_sleep = philo[i].last_eat;
		philo[i].last_thinking = philo[i].last_eat;
		philo[i].env = env;
		if (i % 2 == 0)
		{
			philo[i].fork.r_fork = fork[i];
			philo[i].fork.l_fork = fork[i + 1];
		}
		else
		{
			philo[i].fork.l_fork = fork[i];
			philo[i].fork.r_fork = fork[i + 1];
		}
		if (i == env->argc -1)
			philo[i].fork.l_fork = fork[0];
		i++;
	}
		/*if (i == env->argc -1)
			philo[i].fork.r_fork = fork[0];
		else
			philo[i].fork.r_fork = fork[i + 1];
		philo[i].fork.l_fork = fork[i];*/
}

void	ft_philo_after_life(t_philo *philo, t_env *env)
{
	int	i;

	i = 0;
	(void )philo;
	pthread_mutex_destroy(&env->life);
	while (i < env->argc)
	{
		if (i % 2 == 0)
			pthread_mutex_destroy(&philo->fork.r_fork);
		else
			pthread_mutex_destroy(&philo->fork.l_fork);
		i++;
	}
}
