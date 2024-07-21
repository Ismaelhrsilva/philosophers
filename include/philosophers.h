/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:53:02 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/20 21:44:28 by ishenriq         ###   ########.fr       */
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

typedef struct	s_philo
{
	pthread_t	thread;
	int			id;
	t_pmutex	life;
}	t_philo;

typedef struct s_env
{
	int	argc;
}	t_env;

void	ft_putendl_fd(char *s, int fd);
void ft_message(t_philo *philo, char *msg);

#endif

