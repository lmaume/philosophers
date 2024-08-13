/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:23:57 by lmaume            #+#    #+#             */
/*   Updated: 2024/08/13 18:08:44 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// static void death_test_printer(t_monit *table)
// {
// 	printf("is last meal %ld > t-die? philo %d, time to die %d\n", \
// 	((ms_time(table->time) - table->started_at) - table->philo->last_meal), \
// 	table->philo->id, table->time_to_die);
// }

bool	is_dead(t_philo *philo, bool print)
{
	if (((ms_time(philo->table->time) - philo->table->started_at)) - \
					(philo->last_meal) > philo->table->time_to_die)
	{
		// death_test_printer(table);

		if (print == true)
			print_death(philo);
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

void	eating_process(t_philo *philo)
{
	print_fork(philo);
	
	print_fork(philo);

	print_eat(philo);
	
	if (gettimeofday(philo->table->time, NULL) != 0)
		return ;
	philo->table->philo->last_meal = (ms_time(philo->table->time) \
										- philo->table->started_at);
	mssleep(philo->table->time_to_eat);
}

void	could_i_eat(t_philo *philo)
{
	printf("%d wants to eat\n", philo->id);
	pthread_mutex_lock(&philo->fork[philo->id]);
	pthread_mutex_lock(&philo->fork[(philo->id) \
					% philo->table->philo_number]);
	eating_process(philo);
	philo->eat_count++;
		pthread_mutex_unlock(&philo->fork[(philo->id) \
							% philo->table->philo_number]);
		pthread_mutex_unlock(&philo->fork[philo->id]);
}
