/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:12:33 by lmaume            #+#    #+#             */
/*   Updated: 2024/10/18 16:50:14 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	is_entry_valid(int argc, t_monit *table)
{
	if (argc < 5 || argc > 6 || table->philo_number < 1 \
	|| table->time_to_die < 1 || table->time_to_eat < 1 \
	|| table->time_to_sleep < 1 || (argc >= 6 && table->must_eat < 1) \
	|| table->philo_number > 200)
	{
		printf("Invalid arguments.\n");
		if (table->philo_number < 1)
			printf("Not enough philosophers.\n");
		if (table->philo_number > 200)
			printf("Too much philosophers.\n");
		if (table->time_to_die < 1)
			printf("Time to die below 1.\n");
		if (table->time_to_eat < 1)
			printf("Time to eat below 1.\n");
		if (table->time_to_sleep < 1)
			printf("Time to sleep below 1.\n");
		if (argc >= 6 && table->must_eat < 1)
			printf("Number of times each philosopher must eat si below 1.\n");
		if (argc < 5 || argc > 6)
			printf("Not enough or too much args.\n");
		return (false);
	}
	return (true);
}

void	mssleep(int duration, struct timeval *time)
{
	long int	time_it;
	long int	timer;

	time_it = ms_time(time);
	while (1)
	{
		timer = ms_time(time);
		if (timer - time_it >= duration)
			return ;
		usleep(1000);
	}
}

bool	is_all_eaten(t_philo *philo)
{
	int	i;

	i = 0;
	while (i <= philo->table->philo_number - 1)
	{
		if (philo->table->philo[i].eat_count >= philo->table->must_eat)
			i++;
		else
			return (false);
	}
	pthread_mutex_lock(philo->table->state_right);
	philo->table->end = true;
	pthread_mutex_unlock(philo->table->state_right);
	print_ate(philo);
	return (true);
}
