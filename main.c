#include "Philosophers.h"


t_philosopher *ft_lstnew(int id , t_program_args *args)
{
	t_philosopher *new;
	new = malloc(sizeof(t_philosopher));
	new->id = id;
	new->next = new;
	new->n_meals = 0;
	new->args = args;
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
}

// void ft_routine_manager()
// {
	
// }

void *ft_routine(void *arg)
{
	t_philosopher *philos;

	// pthread_mutex_init(philos->fork, NULL);
	philos = (t_philosopher *) arg;
	pthread_mutex_lock(philos->fork);
	printf("take fork \n");
	pthread_mutex_lock(philos->next->fork);
	printf("take fork and start eating\n");
	usleep(philos->args->t_eat);
	pthread_mutex_unlock(philos->fork);
	pthread_mutex_unlock(philos->next->fork);
	printf("is sleeping \n");
	usleep(philos->args->t_sleep);
	printf("is thinking\n");
	
	return (NULL);
}

void ft_create_threads(t_philosopher *philos)
{
	int i;
	i = philos->args->n_philo;
	while (i--)
	{
		pthread_create(&philos->threadId, NULL, &ft_routine, philos);
		philos = philos->next;
		usleep(1);
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
	// struct timeval current_time, end;
	// gettimeofday(&current_time, NULL);
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
		// while (1 && node)
		// {
		// 	printf("%d ",node->id);
		// 	node = node->next;
		// 	if (head == node)
		// 	{
		// 		printf("\n");
		// 		break;
		// 	}
		// }
	}
	// printf("seconds : %ld\nmicro seconds : %d\n",current_time.tv_sec, current_time.tv_usec);
	// sleep(10);
	// gettimeofday(&end, NULL);
	// printf("seconds : %ld\nmicro seconds : %d\n",(end.tv_sec - current_time.tv_sec), (end.tv_usec - current_time.tv_usec));
	return 0;
}
