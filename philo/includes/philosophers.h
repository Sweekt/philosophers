/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:59:03 by beroy             #+#    #+#             */
/*   Updated: 2024/03/20 13:27:57 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define PHILO_MAX 200
# define ALIVE 1
# define DEAD 0

// COLOR CODES

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"

// DISPLAY

# define LFORK "has taken the left fork."
# define RFORK "has taken the right fork."
# define EAT "is eating.."
# define SLEEP "is sleeping..."
# define THINK "is thinking."
# define DIED "died from a lack of spaghetti... :("

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	unsigned int	nbr_phil;
	unsigned int	ttd;
	unsigned int	tte;
	unsigned int	tts;
	unsigned int	nbr_eat;
	unsigned int 	alive;
	long int		last_meal;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*start_lock;
}	t_philo;

// main

void		ft_display(t_philo *philo);

// params_parser

int			ft_is_num(char *str);
int			ft_atoi(char *str);
int			ft_check_args(char **av);

// routine

void		eat(t_philo *philo);
void		sleep_think(t_philo *philo);
void		*routine(void *data);

// init

void		content_init(t_philo *philo, int ac, char **av, int i);
t_philo		*philo_init(int ac, char **av);

// time

long int	time_now(void);
void		ft_usleep(long int time);

// monitoring

void		ft_write(t_philo *philo, char *str, char *color);
int 		check_status(t_philo *philo);
void		*monitoring(void *data);

#endif