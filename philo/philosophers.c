/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:13:05 by lmaume            #+#    #+#             */
/*   Updated: 2024/06/26 17:59:35 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void	*arg)
{
	t_monit	*table;

	table = arg;
	table->philo->eat_count = 0;
	while (is_dead(table) != true || table->philo->eat_count < table->must_eat)
	{
		if (gettimeofday(table->time, NULL) != 0)
			return (false);
		could_i_eat(table);
		if (gettimeofday(table->time, NULL) != 0)
			return (NULL);
		printf("je suis ici %ld\n", table->time->tv_sec / 1000);
		printf("\e[1;34m%ld %d is speeping.\e[0m\n", (table->time->tv_usec - table->started_at), table->philo->it + 1);
		mssleep(table->time_to_sleep);
	}
	if (table->philo->eat_count < table->must_eat)
	{
		printf("\e[1;31m%ld evrerybody ate.\e[0m\n", (table->time->tv_usec / 1000 - table->started_at));
	}
	else
	{
		if (gettimeofday(table->time, NULL) != 0)
			return (NULL);
		printf("\e[1;31m%ld %d died.\e[0m\n", (table->time->tv_usec / 1000 - table->started_at), table->philo->it + 1);
	}
	return (arg);
}

bool	thread_init(t_monit *table)
{
	table->philo->it = 0;
	while (table->philo->it < table->philo_number)
	{
		if (pthread_mutex_init(table->philo->fork, NULL) != 0)
			exit(1);
		if (pthread_create(&table->philo->philo[table->philo->it], \
							NULL, (void *)routine, table) != 0)
			exit(1);
		if (pthread_join(table->philo->philo[table->philo->it], \
											NULL) != 0)
			exit(1);
		if (pthread_mutex_destroy(table->philo->fork) != 0)
			exit(1);
		table->philo->it++;
	}
	return (true);
}

// TODO : Thread to verify death.
bool	thread_maker(t_monit *table)
{
	table->philo = malloc(sizeof(t_philo) * table->philo_number);
	table->philo->philo = malloc(sizeof(pthread_t) * table->philo_number);
	table->philo->fork = malloc(sizeof(pthread_mutex_t) * table->philo_number);
	thread_init(table);
	free(table->philo);
	free(table->philo->philo);
	free(table->philo->fork);
	return (true);
}

bool	init_structure(t_monit	*table, int argc, char **argv)
{
	if (argc < 5)
		return (false);
	table->started_at = (table->time->tv_usec / 1000);
	table->philo_number = ft_atoi(argv[1], NULL);
	table->time_to_die = ft_atoi(argv[2], NULL);
	table->time_to_eat = ft_atoi(argv[3], NULL);
	table->time_to_sleep = ft_atoi(argv[4], NULL);
	if (argv[5] != NULL)
		table->must_eat = ft_atoi(argv[5], NULL);
	return (true);
}

int	main(int argc, char **argv)
{
	t_monit	table;

	init_structure(&table, argc, argv);
	if (is_entry_valid(argc, &table) == false)
		return (1);
	if (thread_maker(&table) == false)
		return (1);
	sleep(3);
	return (0);
}
