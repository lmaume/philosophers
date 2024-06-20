/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:04:46 by lmaume            #+#    #+#             */
/*   Updated: 2024/06/20 11:57:24 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdbool.h>

// ? BASE FUNCTIONS (LIB SUBSTITUTE) :
size_t	ft_strlen(const char *str);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_atoi(char *nptr, int *error);

// ? PARSING FUNCTIONS :
bool	is_entry_valid(int argc, char **argv);

typedef struct s_philo
{
	// [struct to fill]
}				t_philo;
#endif