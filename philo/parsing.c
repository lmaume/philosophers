/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:12:33 by lmaume            #+#    #+#             */
/*   Updated: 2024/06/20 15:05:34 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	is_entry_valid(int argc, char **argv)
{
	if (argc < 5 || ft_atoi(argv[1], NULL) < 1)
	{
		printf("false\n");
		return (false);
	}
	return (true);
}
