/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:54:05 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/27 18:09:23 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->env->n_philo == 1)
	{
		ft_message(philo, "has taken a fork", ft_time_now() - philo->born);
		ft_message(philo, "has taken a fork", ft_time_now() - philo->born);
		ft_message(philo, "is sleeping", ft_time_now() - philo->born);
		ft_message(philo, "died", ft_time_now() - philo->born);
		return (arg);
	}
	while (philo->n_eat < philo->env->n_eat)
	{
		ft_eating(philo);
		ft_sleeping(philo);
		pthread_mutex_lock(&philo->env->life);
		if (philo->env->started == 1)
		{
			pthread_mutex_unlock(&philo->env->life);
			break ;
		}
		pthread_mutex_unlock(&philo->env->life);
		ft_message(philo, "is thinking", ft_time_now() - philo->born);
	}
	return (arg);
}

void	ft_eating_aux(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->life);
	if (philo->env->started != 1)
	{
		pthread_mutex_unlock(&philo->env->life);
		ft_message(philo, "has taken a fork", ft_time_now() - philo->born);
		pthread_mutex_lock(&philo->env->life);
		philo->n_eat++;
		philo->last_eat = ft_time_now();
		pthread_mutex_unlock(&philo->env->life);
		ft_message(philo, "is eating", ft_time_now() - philo->born);
		usleep(philo->env->time_eat * 1000);
	}
	else
		pthread_mutex_unlock(&philo->env->life);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->life);
	if (philo->env->started == 1)
	{
		pthread_mutex_unlock(&philo->env->life);
		return ;
	}
	pthread_mutex_unlock(&philo->env->life);
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(&philo->env->life);
		if (philo->env->started != 1)
			ft_message(philo, "has taken a fork", ft_time_now() - philo->born);
		pthread_mutex_unlock(&philo->env->life);
		pthread_mutex_lock(philo->r_fork);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		if (philo->env->started != 1)
			ft_message(philo, "has taken a fork", ft_time_now() - philo->born);
		pthread_mutex_lock(philo->l_fork);
	}
	ft_eating_aux(philo);
}

void	ft_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->life);
	if (philo->env->started == 1)
	{
		pthread_mutex_unlock(&philo->env->life);
		return ;
	}
	if (philo->env->n_philo == 1)
	{
		ft_message(philo, "has taken a fork", ft_time_now() - philo->born);
		ft_message(philo, "has taken a fork", ft_time_now() - philo->born);
	}
	pthread_mutex_unlock(&philo->env->life);
	ft_message(philo, "is sleeping", ft_time_now() - philo->born);
	usleep(philo->env->time_sleep * 1000);
	usleep(philo->env->time_die / 10 * 1000);
}

void	ft_philo_born(t_philo *philo, t_env *env, t_monitor *monitor)
{
	t_pmutex	*fork;
	static int	i;

	pthread_mutex_init(&env->life, NULL);
	pthread_mutex_init(&env->write, NULL);
	fork = ft_create_mutex(env);
	env->fork = fork;
	env->time_begin = ft_time_now();
	while (i < env->argc)
	{
		philo[i].id = i;
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
