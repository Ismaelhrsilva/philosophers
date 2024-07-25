/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:54:05 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/25 20:50:22 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
# include <pthread.h>


void	*ft_monitoring(void *arg)
{
	t_monitor	*monitor;
	int last_eat;
	int	time_die;
	int	i;

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
			ft_message(&monitor->philo[i], "died",
			  ft_time_now() - monitor->philo[i].born);
			break ;
		}
		i++;
	}
	return (arg);
}

int	main(int argc, char **argv)
{
	int	i;
	t_philo	*philo;
	t_monitor	*monitor;
	t_env	*env;

	(void )argc;
	env = malloc(sizeof(t_env));
	monitor = malloc(sizeof(t_monitor));
	philo = malloc(200 * sizeof(t_philo));
	if (ft_args(argc, argv, env))
		exit(0);
	ft_philo_born(philo, env, monitor);
	i = 0;
	while (i < env->argc)
	{
		usleep(1 * 1000);
		pthread_create(&philo[i].thread, NULL, &ft_life, &philo[i]);
		i++;
	}
	i = 0;
	pthread_create(&monitor->thread, NULL, &ft_monitoring, monitor);
	i = 0;
	while (i < env->argc)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	i = 0;
	pthread_join(monitor->thread, NULL);
	ft_philo_after_life(philo, env);
	return (0);
}
