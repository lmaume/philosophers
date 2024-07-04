/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:50:03 by lmaume            #+#    #+#             */
/*   Updated: 2024/07/04 17:44:51 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_sleep(t_monit *table)
{
	if (pthread_mutex_lock(&table->print_right) == 0)
	{
		printf("\e[1;31m%ld everybody ate.\e[0m\n", \
			(ms_time(table->time) - table->started_at));
		table->end = true;
		pthread_mutex_unlock(&table->print_right);
	}
}

// void	print_fork(t_monit *table)
// {
	
// }

// void	print_eat(t_monit *table)
// {
	
// }
