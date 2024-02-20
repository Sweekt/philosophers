/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:58:57 by beroy             #+#    #+#             */
/*   Updated: 2024/02/20 16:44:34 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_parse(char **av, t_params params)
{
	
}

int	main(int ac, char **av)
{
	t_params	params;

	if (ac < 5 || ac > 6)
		return (printf("Wrong arguments input!"), 0);
	ft_parse(av, params);
	return (0);
}
