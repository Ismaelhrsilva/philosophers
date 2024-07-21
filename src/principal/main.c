/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:54:05 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/20 21:49:41 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
# include <pthread.h>

/*void	*ft_life(void *arg)
{
	//(void )arg;
	pthread_mutex_t	life;

	pthread_mutex_init(&life, NULL);
	ft_eat();
	pthread_mutex_destroy(&life);

	pthread_mutex_init(&life, NULL);
	ft_sleeping();
	pthread_mutex_destroy(&life);
	
	pthread_mutex_init(&life, NULL);
	ft_thinking();
	pthread_mutex_destroy(&life);

	return (arg);
}*/

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
	while (i < env->argc)
	{
		philo[i]->id = i;
		pthread_mutex_init(&philo[i]->life, NULL);
		i++;
	}
}

void	ft_philo_after_life(t_philo **philo, t_env *env)
{
	int	i;

	i = 0;
	while (i < env->argc)
	{
		pthread_mutex_destroy(&philo[i]->life);
		i++;
	}
}


int	main(int argc, char **argv)
{
	int	i;
	t_philo	*philo;
	t_env	*env;

	(void )argv;
	philo = malloc(20 * sizeof(t_philo *));
	env = malloc(sizeof(t_env));
	env->argc = argc;
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
