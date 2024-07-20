/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:54:05 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/20 20:06:26 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
# include <pthread.h>

void *ft_eat(void *arg)
{
	(void )arg;
	ft_putendl_fd("is eating", STDOUT_FILENO);
	return arg;
}

void *ft_sleeping(void *arg)
{
	(void )arg;
	ft_putendl_fd("is sleeping", STDOUT_FILENO);
	return arg;
}

void *ft_thinking(void *arg)
{
	(void )arg;
	ft_putendl_fd("is thinking", STDOUT_FILENO);
	return arg;
}

int	main(void)
{
	pthread_t	philo;
	pthread_mutex_t	life;

	pthread_mutex_init(&life, NULL);
	pthread_create(&philo, NULL, &ft_eat, NULL);
	pthread_create(&philo, NULL, &ft_sleeping, NULL);
	pthread_create(&philo, NULL, &ft_thinking, NULL);
	pthread_join(philo, NULL);
	pthread_mutex_destroy(&life);
	return (0);
}
