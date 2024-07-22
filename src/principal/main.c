/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:54:05 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/22 19:11:51 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
# include <pthread.h>

void	*ft_life(void *arg)
{
	t_philo *philo;
	int	i;

	philo = (t_philo *)arg;
	i = 0;
	while (i < 10)
	{
		usleep(300);
		philo->last_eat = ft_time_now() - philo->born;
		ft_message(philo, "is eating", philo->last_eat);
		usleep(300);
		philo->last_sleep= ft_time_now() - philo->born;
		ft_message(philo, "is sleeping", philo->last_sleep);
		usleep(300);
		philo->last_thinking = ft_time_now() - philo->born;
		ft_message(philo, "is thinking", philo->last_thinking);
		usleep(300);
		i++;
	}
	return (arg);
}

int	main(int argc, char **argv)
{
	int	i;
	t_philo	philo[200];
	t_env	*env;

	(void )argc;
	env = malloc(sizeof(t_env));
	if (argv[1] != NULL)
		env->argc = ft_atoi(argv[1]);
	else
		env->argc = 1;
	ft_philo_born(philo, env);
	i = 0;
	while (i < env->argc)
	{
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
