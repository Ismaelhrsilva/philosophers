/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:54:05 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/20 23:24:53 by ishenriq         ###   ########.fr       */
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

void	ft_philo_born(t_philo **philo, t_env *env)
{
	int	i;

	i = 0;
	pthread_mutex_init(&env->life, NULL);
	while (i < env->argc)
	{
		//philo[i]->id = malloc(sizeof(int *));
		philo[i]->id = &i ;
		philo[i]->life = env->life;
		if (i == env->argc - 1)
			*philo[i]->id = 4 ;
		i++;
	}
}

void	ft_philo_after_life(t_philo **philo, t_env *env)
{
	int	i;

	i = 0;
	(void )philo;
	pthread_mutex_destroy(&env->life);
	/*while (i < env->argc)
	{
		i++;
	}*/
}


int	main(int argc, char **argv)
{
	int	i;
	t_philo	*philo;
	t_env	*env;

	(void )argc;
	philo = malloc(20 * sizeof(t_philo *));
	env = malloc(sizeof(t_env));
	if (argv[1] != NULL)
		env->argc = ft_atoi(argv[1]);
	else
		env->argc = 1;
	ft_philo_born(&philo, env);
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
	ft_philo_after_life(&philo, env);
	return (0);
}
