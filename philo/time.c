/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:23:57 by lmaume            #+#    #+#             */
/*   Updated: 2024/10/28 14:52:41 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	is_dead(t_philo *philo)
{
	if (((ms_time(&philo->table->time) - philo->table->started_at)) - \
						(philo->last_meal) > philo->table->time_to_die)
	{
		pthread_mutex_lock(philo->table->state_right);
		philo->table->end = true;
		pthread_mutex_unlock(philo->table->state_right);
		print_death(philo);
		return (true);
	}
	return (false);
}

long	ms_time(struct timeval *time)
{
	if (gettimeofday( time, NULL) != 0)
		return (-1);
	return ((time->tv_sec * 1000 + time->tv_usec / 1000));
}

static void	eating_process(t_philo *philo)
{
	if (philo->table->end == false && is_dead(philo) == false)
	{
		print_fork(philo);
		if (philo->table->end == false && is_dead(philo) == false)
		{
			print_fork(philo);
			if (philo->table->end == false && is_dead(philo) == false)
			{
				print_eat(philo);
				if (gettimeofday(&philo->table->time, NULL) != 0)
					return ;
				philo->last_meal = (ms_time(&philo->table->time) \
											- philo->table->started_at);
				mssleep(philo->table->time_to_eat, &philo->table->time);
			}
		}
	}
	return ;
}

static void	unlock_forks(t_philo *philo, int opt)
{
	pthread_mutex_unlock(philo->fork);
	if (opt == 2)
	{
		pthread_mutex_unlock(philo->table->philo[philo->id \
						% philo->table->philo_number].fork);
	}
	return ;
}

void	could_i_eat(t_philo *philo)
{
	if (philo->table->is_limited == true)
	if (is_all_eaten(philo) == true )
		return ;
	pthread_mutex_lock(philo->fork);


	if (philo->table->end == false && is_dead(philo) == false)
	{
		pthread_mutex_lock(philo->table->philo[philo->id \
					% philo->table->philo_number].fork);
		if (philo->table->end == false || is_dead(philo) == true)
			eating_process(philo);
		unlock_forks(philo, 2);
		philo->eat_count++;
		return ;
	}
	unlock_forks(philo, 1);
	return ;
}
