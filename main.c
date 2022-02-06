#include "Philosophers.h"


t_philosopher *ft_lstnew(int id , t_program_args *args)
{
	t_philosopher *new;
	new = malloc(sizeof(t_philosopher));
	pthread_mutex_init(&new->fork, NULL);
	new->id = id;
	new->next = new;
	new->n_meals = 0;
	new->args = args;
	new->iseating = 0;
	return (new);
}

t_philosopher *ft_lstlast(t_philosopher *head)
{
	t_philosopher *tmp;

	tmp = head;
	while (1 && head)
	{
		head = head->next;
		if (head->next == tmp)
			return (head);
	}
	return (head);
}

void ft_lstadd_back(t_philosopher **lst, t_philosopher *new)
{
	t_philosopher *last;
	if (lst)
	{
		if (new)
		{
			last = ft_lstlast(*lst);
			last->next = new;
			new->next = (*lst);
		}
	}
	else
		(*lst) = new;
}

void ft_args_init(t_program_args *args, char **argv)
{
	args->n_philo = atoi(argv[0]);
	args->t_die = atoi(argv[1]);
	args->t_eat = atoi(argv[2]);
	args->t_sleep = atoi(argv[3]);
	if (argv[4])
		args->n_meals = atoi(argv[4]);
	else
		args->n_meals = -1;
	args->t_now = time_now();
	pthread_mutex_init(&args->write, NULL);
}

void ft_routine_manager(t_philosopher *philos)
{
	int	done;

	done = 0;
	while (1)
	{
		if (philos->id && (time_now() - philos->t_start > philos->args->t_die) && philos->iseating == 0)
		{
			ft_write(philos, "is died\n" ,time_now());
			pthread_mutex_lock(&philos->args->write);
			return ;
		}
		philos = philos->next;
	}
}

void ft_sleep_ms(int time)
{
	usleep(time * 1000);
}

void ft_write(t_philosopher *philo , char *msg, long long time)
{
	pthread_mutex_lock(&philo->args->write);
	printf("%lld philo %d %s",time - philo->args->t_now ,philo->id,msg);	
	pthread_mutex_unlock(&philo->args->write);
}

void	ft_usleep(long long sleep_time)
{
	long long	start;

	start = time_now();
	usleep((sleep_time - 5) * 1000);
	while ((time_now() - sleep_time) < start)
		;
}

long time_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void *ft_routine(void *arg)
{
	t_philosopher *philos;

	philos = (t_philosopher *) arg;
	while (philos->args->n_meals != philos->n_meals)
	{
		pthread_mutex_lock(&philos->fork);
		ft_write(philos , "has taken afork\n", time_now());
		pthread_mutex_lock(&philos->next->fork);
		philos->t_start = time_now();
		ft_write(philos,"is eating\n",time_now());
		philos->iseating = 1;
		ft_usleep(philos->args->t_eat);
		philos->iseating = 0;
		philos->n_meals++;
		pthread_mutex_unlock(&philos->fork);
		pthread_mutex_unlock(&philos->next->fork);
		ft_write(philos,"is sleeping\n",time_now());
		ft_usleep(philos->args->t_sleep);
		ft_write(philos,"is thinking\n",time_now());
	}
	return (NULL);
}

void ft_create_threads(t_philosopher *philos)
{
	int i;
	i = philos->args->n_philo;
	while (i--)
	{
		pthread_create(&philos->threadId, NULL, &ft_routine, philos);
		philos->t_start = philos->args->t_now;
		philos = philos->next;
		usleep(25);
	}
}

t_philosopher *ft_philos_init(t_program_args *args)
{
	int i;
	int j;
	t_philosopher *head;

	j = 1;
	i = args->n_philo;
	head = ft_lstnew(j++, args);
	while (j <= i)
		ft_lstadd_back(&head, ft_lstnew(j++, args));
	return (head);
}

int main(int argc, char **argv)
{
	t_program_args *args;
	t_philosopher *node;
	t_philosopher *head;

	args = malloc(sizeof(t_program_args));
	if (argc >= 5 && argc <= 6)
	{
		ft_args_init(args, &argv[1]);
		node = ft_philos_init(args);
		head = node;
		ft_create_threads(node);
		ft_routine_manager(node);
	}
	return 0;
}
