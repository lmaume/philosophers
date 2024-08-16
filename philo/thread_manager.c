/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:02:51 by lmaume            #+#    #+#             */
/*   Updated: 2024/08/16 18:12:42 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_fork(t_monit *table)
{
	int	i;

	i = 0;
	while (i < table->philo_number)
	{
		if (pthread_mutex_init(table->philo[i].fork, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	clean_forks(t_monit *table)
{
	int	i;

	i = 0;
	while (i < table->philo_number)
	{
		pthread_mutex_destroy(table->philo[i].fork);
		free(table->philo[i].fork);
		i++;
	}
	return ;
}

void	init_philo(t_monit *table)
{
	int	i;

	i = 0;
	while (i < table->philo_number)
	{
		table->philo[i].id = i + 1;
		table->philo[i].fork = malloc(sizeof(pthread_mutex_t));
		table->philo[i].table = table;
		i++;
	}
}

bool	thread_join(t_monit *table)
{
	size_t	i;

	i = 0;
	while (i < (size_t)table->philo_number)
	{
		if (pthread_join(table->philo[i].philo, NULL) != 0)
			return (1);
		i++;
	}
	return (true);
}

bool	thread_maker(t_monit *table)
{
	table->philo = ft_calloc(sizeof(t_philo), table->philo_number);
	table->print_right = ft_calloc(sizeof(pthread_mutex_t), 1);
	thread_init(table);
	return (true);
}
