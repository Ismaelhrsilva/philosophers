/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:53:02 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/27 18:04:19 by ishenriq         ###   ########.fr       */
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

typedef pthread_mutex_t	t_pmutex;

typedef struct s_env
{
	int			argc;
	t_pmutex	life;
	suseconds_t	time_begin;
	int			n_philo;
	int			time_die;
	int			time_eat;
	int			time_sleep;
	int			n_eat;
	int			started;
	t_pmutex	*fork;
}	t_env;

typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	suseconds_t	born;
	suseconds_t	last_eat;
	int			n_eat;
	t_pmutex	*r_fork;
	t_pmutex	*l_fork;
	t_env		*env;
}	t_philo;

typedef struct s_monitor
{
	pthread_t	thread;
	t_env		*env;
	t_philo		*philo;
}	t_monitor;

//File Utils
void		ft_args(int argc, char **argv, t_env *env);
void		ft_message(t_philo *philo, char *msg, suseconds_t time);
suseconds_t	ft_time_now(void);
t_pmutex	*ft_create_mutex(t_env *env);
int			ft_atoi(const char *nptr);
void		ft_putendl_fd(char *s, int fd);

//File Routines;
void		*ft_life(void *arg);
void		ft_sleeping(t_philo *philo);
void		ft_eating(t_philo *philo);
void		ft_philo_born(t_philo *philo, t_env *env, t_monitor *monitor);
void		ft_philo_after_life(t_philo *philo, t_env *env);

//File monitoring
void		*ft_monitoring(void *arg);

#endif
