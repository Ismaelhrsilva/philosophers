/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:54:05 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/20 20:15:44 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
# include <pthread.h>

void	*ft_life(void *arg)
{
	(void )arg;
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
}

int	main(void)
{
	pthread_t	philo;

	pthread_create(&philo, NULL, &ft_life, NULL);
	pthread_join(philo, NULL);
	return (0);
}
