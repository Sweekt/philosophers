/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:59:03 by beroy             #+#    #+#             */
/*   Updated: 2024/02/21 09:13:09 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>

typedef struct s_params
{
	unsigned int	nbr_phil;
	unsigned int	ttd;
	unsigned int	tte;
	unsigned int	tts;
	unsigned int	nbr_eat;
}	t_params;

// params_parser

int	ft_parse(int ac, char **av, t_params *params);
int	ft_check_params(char **av);
int ft_is_num(char *str);
int ft_atoi(char *str);
int ft_check_value(t_params *params);

// philo_utils

void	ft_display(t_params *params);

#endif