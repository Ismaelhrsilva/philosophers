/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:53:02 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/22 19:28:28 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef pthread_mutex_t t_pmutex;

typedef struct s_env
{
	int	argc;
	t_pmutex	life;
	suseconds_t time_begin;
	int		n_philo;
	int 	time_die;
	int 	time_eat;
	int		time_sleep;
	int		n_eat;
}	t_env;

typedef struct	s_philo
{
	pthread_t	thread;
	int			id;
	t_pmutex	life;
	suseconds_t	born;
	suseconds_t	last_eat;
	suseconds_t	last_sleep;
	suseconds_t	last_thinking;
	t_env		*env;
}	t_philo;

int	ft_atoi(const char *nptr);
void	ft_putendl_fd(char *s, int fd);

void ft_message(t_philo *philo, char *msg, suseconds_t time);
suseconds_t	ft_time_now(void);
void	ft_philo_born(t_philo *philo, t_env *env);
void	ft_philo_after_life(t_philo *philo, t_env *env);

#endif

