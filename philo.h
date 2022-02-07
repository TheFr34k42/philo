/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 17:12:51 by ytaya             #+#    #+#             */
/*   Updated: 2022/02/07 23:46:04 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_program_args
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_meals;
	long			t_initphilo;
	pthread_mutex_t	write;
	int				stop;

}t_program_args;

typedef struct s_philosopher
{
	long					t_lastmeal;
	pthread_t				thread_id;
	int						id;
	int						n_meals;
	int						iseating;
	pthread_mutex_t			fork;
	t_program_args			*args;
	struct s_philosopher	*next;
}t_philosopher;

t_philosopher	*ft_lstnew(int id, t_program_args *args);
t_philosopher	*ft_lstlast(t_philosopher *head);
void			ft_args_init(t_program_args *args, char **argv);
void			ft_routine_manager(t_philosopher *philos);
void			ft_sleep_ms(int time);
void			ft_write(t_philosopher *philo, char *msg, long long time);
long			ft_time_now(void);
void			*ft_routine(void *arg);
void			ft_create_threads(t_philosopher *philos);
t_philosopher	*ft_philos_init(t_program_args *args);
void			ft_lstadd_back(t_philosopher **lst, t_philosopher *new);

#endif