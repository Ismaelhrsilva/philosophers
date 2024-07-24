/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:54:05 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/24 20:17:39 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_eating(t_philo *philo, t_env *env)
{
	pthread_mutex_lock(philo->r_fork);
	ft_message(philo, "has taken a fork", ft_time_now() - philo->born);
	pthread_mutex_lock(philo->l_fork);
	ft_message(philo, "has taken a fork", ft_time_now() - philo->born);
	ft_message(philo, "is eating", ft_time_now() - philo->born);
	usleep(philo->env->time_eat * 1000);
	philo->last_eat = ft_time_now() - philo->born;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	ft_sleeping(t_philo *philo, t_env *env)
{
	ft_message(philo, "is sleeping", ft_time_now() - philo->born);
	usleep(philo->env->time_sleep * 1000);
	philo->last_sleep= ft_time_now() - philo->born;
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
		if (i == env->argc - 1)
			philo[i].l_fork = &fork[0];
		else
			philo[i].l_fork = &fork[i + 1];
		philo[i].r_fork = &fork[i];
		i++;
	}
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
			pthread_mutex_destroy(philo->r_fork);
		else
			pthread_mutex_destroy(philo->l_fork);
		i++;
	}
}
