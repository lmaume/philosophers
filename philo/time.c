/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:23:57 by lmaume            #+#    #+#             */
/*   Updated: 2024/07/24 15:10:27 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void death_test_printer(t_monit *table)
{
	printf("is last meal %ld > t-die? philo %d, time to die %d\n", \
	((ms_time(table->time) - table->started_at) - table->philo->last_meal), \
	table->philo->it + 1, table->time_to_die);
}

bool	is_dead(t_monit *table, bool print)
{
	if (((ms_time(table->time) - table->started_at)) - \
			(table->philo->last_meal) > table->time_to_die)
	{
		death_test_printer(table);

		if (print == true)
			print_death(table);
		return (true);
	}
	return (false);
}

long	ms_time(struct timeval *time)
{
	if (gettimeofday(time, NULL) != 0)
		return (-1);
	return ((time->tv_sec * 1000 + time->tv_usec / 1000));
}

void	eating_process(t_monit *table, int *did_eat)
{
	print_fork(table);
	
	print_fork(table);

	print_eat(table);
	
	if (gettimeofday(table->time, NULL) != 0)
		return ;
	table->philo->last_meal = (ms_time(table->time) - table->started_at);
	mssleep(table->time_to_eat);
	*did_eat = 1;
}

void	could_i_eat(t_monit *table)
{
	int		did_eat;

	did_eat = 0;
	printf("%d wants to eat\n", table->philo->it + 1);
	if (pthread_mutex_lock(&table->philo->fork[table->philo->it]) != 0 || \
			pthread_mutex_lock(&table->philo->fork[(table->philo->it + 1) \
												% table->philo_number]) != 0)
		print_think(table);
	else
	{
		eating_process(table, &did_eat);
		table->philo->eat_count++;
	}
	if (did_eat == 1)
	{
		pthread_mutex_unlock(&table->philo->fork[table->philo->it]);
		pthread_mutex_unlock(&table->philo->fork[(table->philo->it + 1) \
												% table->philo_number]);
	}
}
