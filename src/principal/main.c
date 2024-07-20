/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:54:05 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/20 19:51:02 by ishenriq         ###   ########.fr       */
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

int	main(void)
{
	pthread_t	philo;

	pthread_create(&philo, NULL, &ft_eat, NULL);
	pthread_join(philo, NULL);
	return (0);
}
