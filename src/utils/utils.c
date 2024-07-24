/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:54:05 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/24 20:12:31 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

suseconds_t	ft_time_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void ft_message(t_philo *philo, char *msg, suseconds_t time)
{
	pthread_mutex_lock(&philo->life);
	printf(" %ld %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->life);
}

t_pmutex	*ft_create_mutex(t_env *env)
{
	int	i;
	t_pmutex	*fork;

	i = 0;
	fork = malloc(env->argc * sizeof(t_pmutex));
	while (i < env->argc)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
	return (fork);
}

