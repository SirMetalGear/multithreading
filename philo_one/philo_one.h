/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorette <mlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 12:00:02 by mlorette          #+#    #+#             */
/*   Updated: 2021/03/30 11:06:28 by mlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

typedef struct	s_data
{
	int				num;
	int				die;
	int				eat;
	int				sleep;
	int				eat_times;
}				t_data;

typedef struct	s_inside
{
	long long		start_time;
	long long		prev_eat;
	int				monitor_status;
	struct timeval	tv;
	int				turn;
	int				finish_eating;
	t_data			philo;
}				t_inside;

typedef struct	s_all
{
	int				turn;
	t_data			philo;
	long long		start_time;
	long long		*prev_eat;
	pthread_t		*thread;
	pthread_t		monitor;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	turn_mutex;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	monitor_mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	time_mutex;
	pthread_mutex_t	join_mutex;
	int				thread_status;
	int				death_status;
	int				eating_finished;
}				t_all;

int				ft_atoi(char *str);
int				all_num(char **str);
void			ft_putstr_fd(char *s, int fd);
char			*ft_itoa(int n);
size_t			ft_strlen(const char *str);
int				philo_write(int turn, long long current_time, t_all *all,
														const char *str);
void			ft_putnbr(ssize_t n);
void			ft_putstr(char *s);
long long		get_time(t_all *all, struct timeval *tv);
int				monitor(t_all *all);
int				monitor_and_struct_init(t_inside *inside, t_all *all);
int				thread_start(t_all *all);
int				cleaner(t_all *all);

#endif
