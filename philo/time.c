/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:23:57 by lmaume            #+#    #+#             */
/*   Updated: 2024/06/28 17:44:28 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	is_dead(t_monit *table, bool print)
{
	if (((ms_time(table->time) - table->started_at)) - (table->philo->last_meal) > table->time_to_die)
	{
		printf("is last meal %ld > t-die? %d for philo %d, time to die %d\n", \
		((ms_time(table->time) - table->started_at) - table->philo->last_meal), table->time_to_die, table->philo->it + 1, table->time_to_die);
		if (print == true)
			printf("\e[1;31m%ld %d died.\e[0m\n", (ms_time(table->time) - table->started_at), table->philo->it + 1);
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
	printf("\e[0;32m%ld %d has taken a fork.\e[0m\n", \
	(ms_time(table->time) - table->started_at), table->philo->it + 1);
	printf("");
	printf("\e[0;32m%ld %d has taken a fork.\e[0m\n", \
	(ms_time(table->time) - table->started_at), table->philo->it + 1);

	printf("\e[1;32m%ld %d is eating.\e[0m\n", \
	(ms_time(table->time) - table->started_at), table->philo->it + 1);

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
		printf("\e[1;33m%ld %d is thinking.\e[0m\n", \
		(ms_time(table->time) - table->started_at), table->philo->it + 1);
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
