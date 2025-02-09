/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:54:05 by ishenriq          #+#    #+#             */
/*   Updated: 2024/08/01 19:05:55 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

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
		usleep(1 * 10);
		if (i % 2 == 0)
			pthread_create(&philo[i].thread, NULL, &ft_life, &philo[i]);
		i++;
	}
	i = 0;
	while (i < env->argc)
	{
		usleep(1 * 10);
		if (i % 2 != 0)
			pthread_create(&philo[i].thread, NULL, &ft_life, &philo[i]);
		i++;
	}
}

int	ft_one_philo(t_philo *philo)
{
	if (philo->env->n_philo == 1)
	{
		ft_message(philo, "has taken a fork", ft_time_now() - philo->born);
		ft_message(philo, "has taken a fork", ft_time_now() - philo->born);
		ft_message(philo, "is sleeping", ft_time_now() - philo->born);
		usleep(philo->env->time_die * 1000);
		ft_message(philo, "died", ft_time_now() - philo->born);
		return (1);
	}
	else
		return (0);
}

int	main(int argc, char **argv)
{
	static int	i;
	t_philo		*philo;
	t_monitor	*monitor;
	t_env		*env;

	env = malloc(sizeof(t_env));
	monitor = malloc(sizeof(t_monitor));
	philo = malloc(200 * sizeof(t_philo));
	ft_args(argc, argv, env);
	ft_philo_born(philo, env, monitor);
	if (!ft_one_philo(philo))
	{
		ft_create_thread(env, philo);
		if (env->n_philo != 1)
			pthread_create(&monitor->thread, NULL, &ft_monitoring, monitor);
		while (i < env->argc)
			pthread_join(philo[i++].thread, NULL);
		if (env->n_philo != 1)
			pthread_join(monitor->thread, NULL);
	}
	return (ft_philo_after_life(philo, env), ft_free(env, monitor, philo), 0);
}
