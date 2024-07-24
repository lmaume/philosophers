/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:50:03 by lmaume            #+#    #+#             */
/*   Updated: 2024/07/24 13:46:34 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_ate(t_monit *table)
{
// 	if (pthread_mutex_lock(&table->print_right) == 0)
// 	{
	printf("\e[1;31m%ld everybody ate.\e[0m\n", \
		(ms_time(table->time) - table->started_at));
	// pthread_mutex_unlock(&table->print_right);
	// }
}

void	print_sleep(t_monit *table)
{
	// if (pthread_mutex_lock(&table->print_right) == 0)
	// {
	printf("\e[1;34m%ld %d is sleeping.\e[0m\n", \
		(ms_time(table->time) - table->started_at), table->philo->it + 1);
	// pthread_mutex_unlock(&table->print_right);
	// }
}

void	print_fork(t_monit *table)
{
	// if (pthread_mutex_lock(&table->print_right) == 0)
	// {
	printf("\e[0;32m%ld %d has taken a fork.\e[0m\n", \
		(ms_time(table->time) - table->started_at), table->philo->it + 1);
	// pthread_mutex_unlock(&table->print_right);
	// }
}

void	print_eat(t_monit *table)
{
	// if (pthread_mutex_lock(&table->print_right) == 0)
	// {
	printf("\e[1;32m%ld %d is eating.\e[0m\n", \
		(ms_time(table->time) - table->started_at), table->philo->it + 1);
	// pthread_mutex_unlock(&table->print_right);
	// }
}

void	print_think(t_monit *table)
{
	// if (pthread_mutex_lock(&table->print_right) == 0)
	// {
	printf("\e[1;33m%ld %d is thinking.\e[0m\n", \
		(ms_time(table->time) - table->started_at), table->philo->it + 1);
	// pthread_mutex_unlock(&table->print_right);
	// }
}

void	print_death(t_monit *table)
{
	// if (pthread_mutex_lock(&table->print_right) == 0)
	// {
	printf("\e[1;31m%ld %d died.\e[0m\n", \
		(ms_time(table->time) - table->started_at), table->philo->it + 1);
	// 	pthread_mutex_unlock(&table->print_right);
	// }
}
