/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:12:33 by lmaume            #+#    #+#             */
/*   Updated: 2024/06/25 15:56:32 by lmaume           ###   ########.fr       */
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

void	mssleep(int time)
{
	if (usleep(time * 1000) != 0)
		return ;
}
