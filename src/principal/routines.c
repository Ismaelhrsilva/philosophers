/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:54:05 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/27 16:00:52 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_life(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (philo->n_eat < philo->env->n_eat)
	{
		if (philo->env->n_philo != 1)
			ft_eating(philo, philo->env);
		ft_sleeping(philo, philo->env);
		if (philo->env->n_philo == 1)
		{
			ft_message(philo, "died", ft_time_now() - philo->born);
			break ;
		}
		if (philo->env->started == 1)
			break ;
		ft_message(philo, "is thinking", ft_time_now() - philo->born);
	}
	return (arg);
}

void	ft_eating(t_philo *philo, t_env *env)
{
	if (philo->env->started == 1)
		return ;
	pthread_mutex_lock(philo->r_fork);
	if (philo->env->started != 1)
		ft_message(philo, "has taken a fork", ft_time_now() - philo->born);
	pthread_mutex_lock(philo->l_fork);
	if (philo->env->started != 1)
		ft_message(philo, "has taken a fork", ft_time_now() - philo->born);
	if (philo->env->started != 1)
	{
		philo->n_eat++;
		ft_message(philo, "is eating", ft_time_now() - philo->born);
		usleep(philo->env->time_eat * 1000);
		philo->last_eat = ft_time_now();
	}
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	ft_sleeping(t_philo *philo, t_env *env)
{
	if (philo->env->started == 1)
		return ;
	if (philo->env->n_philo == 1)
	{
		ft_message(philo, "has taken a fork", ft_time_now() - philo->born);
		ft_message(philo, "has taken a fork", ft_time_now() - philo->born);
	}	
	ft_message(philo, "is sleeping", ft_time_now() - philo->born);
	usleep(philo->env->time_sleep * 1000);
}

void	ft_philo_born(t_philo *philo, t_env *env, t_monitor *monitor)
{
	t_pmutex	*fork;
	int	i;

	i = 0;
	pthread_mutex_init(&env->life, NULL);
	fork = ft_create_mutex(env);
	env->fork = fork;
	env->time_begin = ft_time_now();
	while (i < env->argc)
	{
		philo[i].id = i;
		philo[i].life = env->life;
		philo[i].born = env->time_begin;
		philo[i].last_eat = ft_time_now();
		philo[i].n_eat = 0;
		philo[i].env = env;
		if (i == env->argc - 1)
			philo[i].l_fork = &fork[0];
		else
			philo[i].l_fork = &fork[i + 1];
		philo[i].r_fork = &fork[i];
		i++;
	}
	monitor->env = env;
	monitor->philo = philo;
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
	free(env->fork);
}
