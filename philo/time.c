/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:23:57 by lmaume            #+#    #+#             */
/*   Updated: 2024/06/26 17:37:39 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	is_dead(t_monit *table)
{

	printf("last meal %ld, time to die %d\n", (table->philo->last_meal - table->started_at), table->time_to_die);
	printf("real last meal %ld\n", table->philo->last_meal);
	if ((table->philo->last_meal - table->started_at) > table->time_to_die)
		return (true);
	return (false);
}

void	eating_process(t_monit *table, int *did_eat)
{
	printf("\e[0;32m%ld %d has taken a fork.\e[0m\n", \
	(table->time->tv_usec / 1000 - table->started_at), table->philo->it + 1);
	printf("\e[0;32m%ld %d has taken a fork.\e[0m\n", \
	(table->time->tv_usec / 1000 - table->started_at), table->philo->it + 1);
	printf("\e[1;32m%ld %d is eating.\e[0m\n", \
	(table->time->tv_usec / 1000 - table->started_at), table->philo->it + 1);
	if (gettimeofday(table->time, NULL) != 0)
		return ;
	table->philo->last_meal = (table->time->tv_usec / 1000);
	mssleep(table->time_to_eat);
	*did_eat = 1;
}

void	could_i_eat(t_monit *table)
{
	int		did_eat;

	did_eat = 0;
	if (pthread_mutex_lock(&table->philo->fork[table->philo->it]) != 0 || \
			pthread_mutex_lock(&table->philo->fork[(table->philo->it + 1) \
												% table->philo_number]) != 0)
		printf("\e[1;33m%ld %d is thinking.\e[0m\n", \
		(table->time->tv_usec / 1000 - table->started_at), table->philo->it + 1);
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
