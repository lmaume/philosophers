/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:12:33 by lmaume            #+#    #+#             */
/*   Updated: 2024/06/21 17:25:02 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	is_entry_valid(int argc, char **argv)
{
	if (argc < 5 || argc > 6 || ft_atoi(argv[1], NULL) < 1)
	{
		printf("Invalid arguments.\n");
		if (ft_atoi(argv[1], NULL) < 1)
			printf("Not enough philosophers.\n");
		if (argc < 5 || argc > 6)
			printf("Not enough or too much args.\n");
		return (false);
	}
	return (true);
}
