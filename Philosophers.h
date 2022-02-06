#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_program_args
{
	int n_philo;
	int t_die;
	int t_eat;
	int t_sleep;
	int n_meals;
	pthread_mutex_t write;
	long t_now;

}t_program_args;

typedef struct s_philosopher
{
	long t_start;
	pthread_t threadId;
	int id;
	pthread_mutex_t fork;
	int n_meals;
	struct s_philosopher *next;
	t_program_args  *args;
	int 			iseating;
}t_philosopher;

long time_now(void);
void	ft_usleep(long long sleep_time);
void ft_write(t_philosopher *philo , char *msg, long long time);

#endif