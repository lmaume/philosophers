/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:13:05 by lmaume            #+#    #+#             */
/*   Updated: 2024/06/21 17:16:48 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*func(void	*arg)
{
	t_philo	*table;

	table = arg;
	printf("\nPhilosopher %d is thinking.", (int)table->it[0]);
	pthread_mutex_lock(&table->m.fork[(int)table->it[0]]);
	pthread_mutex_lock(&table->m.fork[((int)table->it[0] + 1) % 5]);
	printf("\nPhilosopher %d is eating.", (int)table->it[0]);
	sleep(3);
	pthread_mutex_unlock(&table->m.fork[(int)table->it[0]]);
	pthread_mutex_unlock(&table->m.fork[((int)table->it[0] + 1) % 5]);
	printf("\nPhilosopher %d Finished eating ", (int)table->it[0]);
	return (arg);
}

bool	thread_init(t_philo *table)
{
	table->it[0] = 1;
	while (table->it[0] < table->m.philo_number)
	{
		if (pthread_mutex_init(&table->m.fork[table->it[0]], NULL) == -1)
		{
			printf("Failed to initialize the mutex\n");
			exit(1);
		}
		if (pthread_create(&table->m.philo[table->it[0]], NULL, \
							(void *)func, (void *)&table) != 0)
		{
			printf("Error in thread creation.\n");
			exit(1);
		}
		if (pthread_join(table->m.philo[table->it[0]], \
								(void **)&"message\n") != 0)
		{
			printf("Failed to join the thread.\n");
			exit(1);
		}
		if (pthread_mutex_destroy(&table->m.fork[table->it[0]]) != 0)
		{
			printf("Mutex destroyed.\n");
			exit(1);
		}
	}
	return (true);
}

bool	thread_maker(t_philo *table)
{
	pthread_t		*philosopher;
	pthread_mutex_t	*fork;

	philosopher = malloc(sizeof(pthread_t) * table->m.philo_number);
	fork = malloc(sizeof(pthread_mutex_t) * table->m.philo_number);
	table->m.philo = philosopher;
	table->m.fork = fork;
	thread_init(table);
	free(philosopher);
	free(fork);
	return (true);
}

void	init_structure(t_philo	*table, char **argv)
{
	table->m.philo_number = ft_atoi(argv[1], NULL);
	table->m.time_to_die = ft_atoi(argv[2], NULL);
	table->m.time_to_eat = ft_atoi(argv[3], NULL);
	table->m.time_to_sleep = ft_atoi(argv[4], NULL);
	if (argv[5] != NULL)
		table->m.must_eat = ft_atoi(argv[5], NULL);
}

int	main(int argc, char **argv)
{
	t_philo	table;

	init_structure(&table, argv);
	if (is_entry_valid(argc, argv) == false)
		return (1);
	if (argc == 5)
		printf("die%d, eat%d, sleep%d", \
		table.m.time_to_die, table.m.time_to_eat, table.m.time_to_sleep);
	else if (argc == 6)
		printf("die%d, eat%d, sleep%d, must eat%d", \
		table.m.time_to_die, table.m.time_to_eat, table.m.time_to_sleep, table.m.must_eat);
	if (thread_maker(&table) == false)
		return (1);
	sleep(3);
	return (0);
}
