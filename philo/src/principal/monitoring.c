/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 15:00:23 by ishenriq          #+#    #+#             */
/*   Updated: 2024/08/03 16:56:56 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_monitoring(void *arg)
{
	t_monitor	*monitor;
	int			time_die;
	static int	i;

	monitor = (t_monitor *)arg;
	while (1)
	{
		usleep(1 * 1000);
		pthread_mutex_lock(&monitor->env->life);
		if (i == monitor->env->n_philo)
			i = 0;
		time_die = monitor->env->time_die;
		if (ft_time_now() - monitor->philo[i].last_eat > time_die)
		{
			if ((monitor->philo[i].n_eat) != monitor->env->n_eat)
				ft_message(&monitor->philo[i], "died",
					ft_time_now() - monitor->philo[i].born);
			monitor->env->started = 1;
			pthread_mutex_unlock(&monitor->env->life);
			break ;
		}
		pthread_mutex_unlock(&monitor->env->life);
		i++;
	}
	return (arg);
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
