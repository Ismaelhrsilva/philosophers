/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:54:05 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/24 21:04:11 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
# include <pthread.h>

void	*ft_monitoring(void *arg)
{
	t_monitor	*monitor;
	int	i;

	monitor = (t_monitor *)arg;
	return (arg);
}

int	main(int argc, char **argv)
{
	int	i;
	t_philo	philo[200];
	t_monitor	*monitor;
	t_env	*env;

	(void )argc;
	env = malloc(sizeof(t_env));
	monitor = malloc(sizeof(t_monitor));
	if (ft_args(argc, argv, env))
		exit(0);
	ft_philo_born(philo, env, monitor);
	pthread_create(&monitor->thread, NULL, &ft_monitoring, &monitor);
	i = 0;
	while (i < env->argc)
	{
		usleep(1 * 1000);
		pthread_create(&philo[i].thread, NULL, &ft_life, &philo[i]);
		i++;
	}
	i = 0;
	while (i < env->argc)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	ft_philo_after_life(philo, env);
	return (0);
}
