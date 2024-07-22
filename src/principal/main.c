/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:54:05 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/22 17:49:23 by ishenriq         ###   ########.fr       */
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
	while (i < 3)
	{
		ft_message(philo, "is eating");
		usleep(200);
		ft_message(philo, "is sleeping");
		usleep(200);
		ft_message(philo, "is thinking");
		usleep(200);
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
