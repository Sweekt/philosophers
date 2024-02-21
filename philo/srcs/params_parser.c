/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 08:31:00 by beroy             #+#    #+#             */
/*   Updated: 2024/02/21 09:06:22 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int ft_atoi(char *str)
{
	int res;
	int i;

	res = 0;
	i = 0;
	while (str[i])
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	return (res);
}

int ft_is_num(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 59)
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_params(char **av)
{
	int i;

	i = 1;
	while (av[i])
	{
		if (ft_is_num(av[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int ft_check_value(t_params *params)
{
	if (params->nbr_phil == 0)
		return (printf("There should be at least one philosopher at the table!\n"), 1);
	return (0);
}

int	ft_parse(int ac, char **av, t_params *params)
{
	if (ft_check_params(av) == 1)
		return (1);
	params->nbr_phil = ft_atoi(av[1]);
	params->ttd = ft_atoi(av[2]);
	params->tte = ft_atoi(av[3]);
	params->tts = ft_atoi(av[4]);
	if (ac == 6)
		params->nbr_eat = ft_atoi(av[5]);
	if (ft_check_value(params) == 1)
		return (1);
	return (0);
}
