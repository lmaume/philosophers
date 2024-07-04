/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:04:46 by lmaume            #+#    #+#             */
/*   Updated: 2024/07/04 16:41:58 by lmaume           ###   ########.fr       */
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

typedef struct s_philo
{
	int				it;
	int				eat_count;
	suseconds_t		last_meal;
	pthread_t		*philo;
	pthread_mutex_t	*fork;
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
bool	is_dead(t_monit *table, bool print);
void	could_i_eat(t_monit *table);
long	ms_time(struct timeval *time);

// ? PRINTS :
void	print_sleep(t_monit *table);


#endif