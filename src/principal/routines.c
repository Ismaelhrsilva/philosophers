/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:54:05 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/20 20:14:33 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
# include <pthread.h>

void ft_eat(void)
{
	ft_putendl_fd("is eating", STDOUT_FILENO);
}

void ft_sleeping(void)
{
	ft_putendl_fd("is sleeping", STDOUT_FILENO);
}

void ft_thinking(void)
{
	ft_putendl_fd("is thinking", STDOUT_FILENO);
}
