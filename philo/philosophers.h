/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:04:46 by lmaume            #+#    #+#             */
/*   Updated: 2024/08/13 16:52:13 by lmaume           ###   ########.fr       */
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

struct s_monitor;

typedef struct s_philo
{
	int					id;
	int					eat_count;
	suseconds_t			last_meal;
	pthread_t			philo;
	pthread_mutex_t		*fork;
	struct s_monitor	*table;
}						t_philo;

typedef struct s_monitor
{
	int				philo_number;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	long			started_at;
	bool			end;
	bool			is_limited;
	pthread_mutex_t	print_right;
	struct timeval	*time;
	struct s_philo	*philo;
}						t_monit;

// ? BASE FUNCTIONS (LIB SUBSTITUTE) :
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(char *nptr, int *error);

// ? PARSING FUNCTIONS :
bool	is_entry_valid(int argc, t_monit *table);
void	mssleep(int time);

// ? COMPARE DATAS :
bool	is_dead(t_philo *philo, bool print);
void	could_i_eat(t_philo *philo);
long	ms_time(struct timeval *time);

// ? PRINTS :
void	print_ate(t_philo *philo);
void	print_sleep(t_philo *philo);
void	print_fork(t_philo *philo);
void	print_eat(t_philo *philo);
void	print_think(t_philo *philo);
void	print_death(t_philo *philo);

#endif