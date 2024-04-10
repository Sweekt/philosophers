/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 08:31:00 by beroy             #+#    #+#             */
/*   Updated: 2024/04/10 16:41:39 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_atoi(char *str)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (str[i])
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	return (res);
}

int	ft_is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 59)
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_args(char **av)
{
	if (ft_is_num(av[1]) == 0 || ft_atoi(av[1]) < 1
		|| ft_atoi(av[1]) > PHILO_MAX)
		return (printf("Wrong number of Philosophers at the table!\n"), 1);
	if (ft_is_num(av[2]) == 0 || ft_atoi(av[2]) < 1)
		return (printf("Invalid time to die!\n"), 1);
	if (ft_is_num(av[3]) == 0 || ft_atoi(av[3]) < 1)
		return (printf("Invalid time to eat!\n"), 1);
	if (ft_is_num(av[4]) == 0 || ft_atoi(av[4]) < 1)
		return (printf("Invalid time to sleep!\n"), 1);
	if (av[5] && (ft_is_num(av[5]) == 0 || ft_atoi(av[5]) < 1))
		return (printf("Invalid number of meals!\n"), 1);
	return (0);
}
