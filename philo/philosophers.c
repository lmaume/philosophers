/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:13:05 by lmaume            #+#    #+#             */
/*   Updated: 2024/11/15 16:32:04 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_death(t_philo *philo)
{
	pthread_mutex_lock(philo->table->print_right);			// ! on inverse pas les mutex A B -> B A ! //
	printf("\e[1;31m%ld %d died.\e[0m\n", \
		(ms_time(&philo->table->time) - philo->table->started_at), philo->id);
	pthread_mutex_lock(philo->table->state_right);
	philo->table->death_lock = true;
	pthread_mutex_unlock(philo->table->state_right);
	pthread_mutex_unlock(philo->table->print_right);
	return ;
}

static void	*routine(void	*arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id % 2 == 0)
		mssleep(philo, 10, &philo->table->time);	// * on est paire, on attend pour eviter les bousculades
	while (1)
	{
		if (philo->table->end == true)
			return (0);
		print_think(philo);						// * chaque print appelle is_dead
		if (philo->table->end == true)
			return (0);
		could_i_eat(philo);						// * la partie interessante : )
		if (philo->table->end == true)
			return (0);
		print_sleep(philo);
		mssleep(philo, philo->table->time_to_sleep, &philo->table->time);
		if (philo->table->end == true)
			return (0);
	}
	return (0);
}

bool	thread_init(t_monit *table)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(table->print_right, NULL) != 0)
		return (1);
	if (pthread_mutex_init(table->state_right, NULL) != 0)
		return (1);
	init_philo(table);
	init_fork(table);
	if (table->philo_number == 1)
		return (one_philo(&table->philo[0]), true);
	while (i < table->philo_number)
	{
		if (pthread_create(&table->philo[i].philo, NULL, \
					(void *)routine, &table->philo[i]) != 0)
			return (1);
		i++;
	}
	thread_join(table);			// ? ils s'attendent et se detruisent
	return (true);
}

static bool	init_structure(t_monit	*table, int argc, char **argv)
{
	if (argc < 5)
		return (false);
	if (argc == 6)
		table->is_limited = true;
	else
		table->is_limited = false;
	table->death_lock = false;
	table->end = false;
	table->started_at = (ms_time(&table->time));
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
	while (table.end != true)
		sleep(1);
	clean_forks(&table);						// * tout ce qui suit aurait pu etre dans une fonction 
	pthread_mutex_destroy(table.print_right);	// * lave vaisselle mais c'est tres bien comme ca aussi
	pthread_mutex_destroy(table.state_right);
	free(table.print_right);
	free(table.state_right);
	free(table.philo);
	return (0);
}
