/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:50:03 by lmaume            #+#    #+#             */
/*   Updated: 2024/11/15 16:35:52 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_ate(t_philo *philo)
{
	pthread_mutex_lock(philo->table->print_right);
	if (is_dead(philo) == false)					//? mutex, verif, print, mutex....
	{
		printf("\e[1;31m%ld everybody ate.\e[0m\n", \
		(ms_time(&philo->table->time) - philo->table->started_at));
	}
	pthread_mutex_unlock(philo->table->print_right);
}

void	print_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->table->print_right);
	if (is_dead(philo) == false && philo->table->end == false)
	{
		printf("\e[1;34m%ld %d is sleeping.\e[0m\n", \
		(ms_time(&philo->table->time) - philo->table->started_at), philo->id);
	}
	pthread_mutex_unlock(philo->table->print_right);
}

void	print_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->table->print_right);
	if (is_dead(philo) == false && philo->table->end == false)
	{
		printf("\e[0;32m%ld %d has taken a fork.\e[0m\n", \
		(ms_time(&philo->table->time) - philo->table->started_at), philo->id);
	}
	pthread_mutex_unlock(philo->table->print_right);
}

void	print_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->table->print_right);
	if (is_dead(philo) == false && philo->table->end == false)
	{
		printf("\e[1;32m%ld %d is eating.\e[0m\n", \
		(ms_time(&philo->table->time) - philo->table->started_at), philo->id);
	}
	pthread_mutex_unlock(philo->table->print_right);
}

void	print_think(t_philo *philo)
{
	pthread_mutex_lock(philo->table->print_right);
	if (is_dead(philo) == false && philo->table->end == false)
	{
		printf("\e[1;33m%ld %d is thinking.\e[0m\n", \
		(ms_time(&philo->table->time) - philo->table->started_at), philo->id);
	}
	pthread_mutex_unlock(philo->table->print_right);
}
