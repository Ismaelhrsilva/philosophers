/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:54:05 by ishenriq          #+#    #+#             */
/*   Updated: 2024/08/03 11:57:00 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

void	*ft_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->n_eat < philo->env->n_eat)
	{
		pthread_mutex_lock(&philo->env->life);
		if (philo->env->started == 1)
		{
			pthread_mutex_unlock(&philo->env->life);
			break ;
		}
		pthread_mutex_unlock(&philo->env->life);
		ft_eating(philo);
		ft_sleeping(philo);
		ft_thinking(philo);
	}
	return (arg);
}

void	ft_free(t_env *env, t_monitor *monitor, t_philo *philo)
{
	free(env);
	free(monitor);
	free(philo);
}

void	ft_create_thread(t_env *env, t_philo *philo)
{
	static int	i;

	while (i < env->argc)
	{
		usleep(1 * 1);
		if (i % 2 == 0)
			pthread_create(&philo[i].thread, NULL, &ft_life, &philo[i]);
		i++;
	}
	i = 0;
	while (i < env->argc)
	{
		usleep(1 * 1);
		if (i % 2 != 0)
			pthread_create(&philo[i].thread, NULL, &ft_life, &philo[i]);
		i++;
	}
}

void	*ft_one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->l_fork);
	ft_message(philo, "has taken a fork", ft_time_now() - philo->born);
	pthread_mutex_unlock(philo->l_fork);
	usleep(philo->env->time_die * 1000);
	ft_message(philo, "died", ft_time_now() - philo->born);
	ft_philo_after_life(philo, philo->env);
	return (arg);
}

int	main(int argc, char **argv)
{
	static int	i;
	t_philo		*philo;
	t_monitor	*monitor;
	t_env		*env;

	env = malloc(sizeof(t_env));
	ft_args(argc, argv, env);
	monitor = malloc(sizeof(t_monitor));
	philo = malloc(200 * sizeof(t_philo));
	ft_philo_born(philo, env, monitor);
	if (env->n_philo == 1)
	{
		pthread_create(&philo[0].thread, NULL, &ft_one_philo, &philo[0]);
		usleep((philo->env->time_die_2 + 50) * 1000);
		pthread_join(philo->thread, NULL);
		return (ft_free(env, monitor, philo), 0);
	}
	ft_create_thread(env, philo);
	if (env->n_philo != 1)
		pthread_create(&monitor->thread, NULL, &ft_monitoring, monitor);
	while (i < env->argc)
		pthread_join(philo[i++].thread, NULL);
	if (env->n_philo != 1)
		pthread_join(monitor->thread, NULL);
	return (ft_philo_after_life(philo, env), ft_free(env, monitor, philo), 0);
}
