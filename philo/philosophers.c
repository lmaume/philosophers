/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:13:05 by lmaume            #+#    #+#             */
/*   Updated: 2024/06/20 18:37:05 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

	// printf("\nPhilosopher % d is thinking.", (int)arg);
	// pthread_mutex_lock(&arg[(int)arg]);
	// pthread_mutex_lock(&arg[((int)arg + 1) % 5]);
	// printf("\nPhilosopher % d is eating.", (int)arg);
	// sleep(3);
	// pthread_mutex_unlock(&arg[(int)arg]);
	// pthread_mutex_unlock(&arg[((int)arg + 1) % 5]);
	// printf("\nPhilosopher % d Finished eating ", (int)arg);
void	*func(void	*arg)
{
	(void)arg;
	return (arg);
}

bool	thread_init(t_philo *table)
{
	int	i[1];

	i[0] = 1;
	while (i[0] < table->philo_number)
	{
		if (pthread_mutex_init(&table->fork[i[0]], NULL) == -1)
		{
			printf("Failed to initialize the mutex\n");
			exit(1);
		}
		if (pthread_create(&table->philo[i[0]], NULL, \
							(void *)func, (void *)i) != 0)
		{
			printf("Error in thread creation.\n");
			exit(1);
		}
		if (pthread_join(table->philo[i[0]], (void **)&"message\n") != 0)
		{
			printf("Failed to join the thread.\n");
			exit(1);
		}
		if (pthread_mutex_destroy(&table->fork[i[0]]) != 0)
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

	philosopher = malloc(sizeof(pthread_t) * table->philo_number);
	fork = malloc(sizeof(pthread_mutex_t) * table->philo_number);
	table->philo = philosopher;
	table->fork = fork;
	thread_init(table);
	free(philosopher);
	free(fork);
	return (true);
}

int	main(int argc, char **argv)
{
	int		number_of_philo;
	t_philo	table;

	number_of_philo = ft_atoi(argv[1], NULL);
	table.philo_number = number_of_philo;
	if (is_entry_valid(argc, argv) == false)
		return (1);
	if (thread_maker(&table) == false)
		return (1);
	return (0);
}
