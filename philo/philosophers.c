/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:13:05 by lmaume            #+#    #+#             */
/*   Updated: 2024/08/13 17:07:33 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// static void	meal_test_printer(t_monit *table)
// {
// 	printf("last meal %ld of philo %d\n", (ms_time(table->time) - \
// 	table->started_at) - table->philo->last_meal, table->philo->id + 1);
// }

void	*routine(void	*arg)
{
	t_philo	*philo;

	philo = arg;
	
	while (1)
	{
		print_think(philo);
		could_i_eat(philo);
	}

	
	if (is_dead(philo, true) == true)
		return (philo->table->end = true, NULL);
	return (0);
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

int	init_fork(t_monit *table)
{
	int	i;

	i = 0;
	while (i < table->philo_number)
	{
		if (pthread_mutex_init(table->philo[i].fork, NULL) != 0)
			return (3);
		i++;
	}
	return (0);
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

bool	thread_init(t_monit *table)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&table->print_right, NULL) != 0)
		exit(1);
	init_philo(table);
	init_fork(table);
	while (i < table->philo_number)
	{
		if (pthread_create(&table->philo[i].philo, NULL, (void *)routine, &table->philo[i]) != 0)
			exit(1);
		i++;
	}
	thread_join(table);
	return (true);
}

bool	thread_maker(t_monit *table)
{
	table->philo = calloc(sizeof(t_philo), table->philo_number);
	
	thread_init(table);
	
	free(table->philo->fork);
	free(table->philo);
	return (true);
}

bool	init_structure(t_monit	*table, int argc, char **argv)
{
	if (argc < 5)
		return (false);
	if (argc == 6)
		table->is_limited = true;
	else
		table->is_limited = false;
	table->end = false;
	table->started_at = (ms_time(table->time));
	table->philo_number = ft_atoi(argv[1], NULL);
	table->time_to_die = ft_atoi(argv[2], NULL);
	table->time_to_eat = ft_atoi(argv[3], NULL);
	table->time_to_sleep = ft_atoi(argv[4], NULL);
	if (argc == 6 && argv[5] != NULL)
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
	if (pthread_mutex_destroy(table.philo->fork) != 0)
		exit(1);
	while (table.end != true)
		sleep(1);
	return (0);
}
