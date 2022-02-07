name = philo
SRCS = philo.c philo_tools.c philo_tools1.c
all:$(name)

$(name): $(SRCS)
	gcc -Wall -Wextra -Werror $(SRCS) -o $(name)
clean:
	rm -rf $(name)
re:clean all