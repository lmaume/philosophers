/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:04:46 by lmaume            #+#    #+#             */
/*   Updated: 2024/11/15 16:35:08 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

struct	s_monitor;				// ? pour que chaque philo accede a la table, on la prototype avant

typedef struct s_philo			// ! ne pas confondre la struct t_philo et le pthread_t philo
{
	int					id;
	int					eat_count;
	suseconds_t			last_meal;
	pthread_t			philo;
	pthread_mutex_t		*fork;
	struct s_monitor	*table;
}						t_philo;

typedef struct s_monitor		// ? C'est la table
{
	int				philo_number;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	long			started_at;
	bool			end;
	bool			death_lock;
	bool			is_limited;
	pthread_mutex_t	*print_right;
	pthread_mutex_t	*state_right;
	struct timeval	time;
	struct s_philo	*philo;
}						t_monit;

// ? BASE FUNCTIONS (LIB SUBSTITUTE) :
int		ft_atoi(char *nptr, int *error);
void	*ft_calloc(size_t nmemb, size_t size);

// ? PARSING FUNCTIONS :
bool	is_entry_valid(int argc, t_monit *table);
void	mssleep(t_philo *philo, int duration, struct timeval *time);
int		one_philo(t_philo *philo);

// ? THREADS MANAGER :							(ici on appelle toujours la table)
int		init_fork(t_monit *table);
void	clean_forks(t_monit *table);
void	init_philo(t_monit *table);
bool	thread_join(t_monit *table);
bool	thread_maker(t_monit *table);
bool	thread_init(t_monit *table);

// ? COMPARE DATAS :
long	ms_time(struct timeval *time);
bool	is_dead(t_philo *philo);			// *(a partir de la on appelle toujours t_philo)
bool	is_all_eaten(t_philo *philo);
void	could_i_eat(t_philo *philo);

// ? PRINTS :
void	print_ate(t_philo *philo);
void	print_sleep(t_philo *philo);
void	print_fork(t_philo *philo);
void	print_eat(t_philo *philo);
void	print_think(t_philo *philo);
void	print_death(t_philo *philo);

#endif