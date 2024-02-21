/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:58:57 by beroy             #+#    #+#             */
/*   Updated: 2024/02/21 08:53:37 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int ac, char **av)
{
	t_params	params;

	if (ac < 5 || ac > 6)
		return (printf("Wrong arguments input!\n"), 0);
	if (ft_parse(ac, av, &params) == 1)
		return (printf("Wrong arguments input!\n"), 0);
	ft_display(&params);
	return (0);
}
