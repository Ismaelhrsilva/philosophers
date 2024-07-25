/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:54:05 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/25 18:11:34 by ishenriq         ###   ########.fr       */
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

int	ft_args(int argc, char **argv, t_env *env)
{
	if (argc > 6 || argc < 5)
	{
		ft_putendl_fd("error", 2);
		return (1);
	}
	else
	{
		env->started = ft_atoi("0");
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
