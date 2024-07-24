/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:54:05 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/24 20:19:18 by ishenriq         ###   ########.fr       */
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
	while (i < philo->env->n_eat)
	{
		ft_eating(philo, philo->env);
		ft_sleeping(philo, philo->env);
		ft_message(philo, "is thinking", ft_time_now() - philo->born);
		i++;
	}
	return (arg);
}

int	ft_args(int argc, char **argv, t_env *env)
{
	if (argc > 6 || argc < 5)
	{
		ft_putendl_fd("error", 2);
		return (1);
	}
	else
	{
		env->argc	= ft_atoi(argv[1]);
		env->n_philo = ft_atoi(argv[1]);
		env->time_die = ft_atoi(argv[2]);
		env->time_eat = ft_atoi(argv[3]);
		env->time_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			env->n_eat = ft_atoi(argv[5]);
		else
			env->n_eat = ft_atoi("2");
		return (0);
	}
}

int	main(int argc, char **argv)
{
	int	i;
	t_philo	philo[200];
	t_env	*env;

	(void )argc;
	env = malloc(sizeof(t_env));
	if (ft_args(argc, argv, env))
		exit(0);
	ft_philo_born(philo, env);
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
