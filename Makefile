name = philo
all:
	gcc main.c -o $(name)
clean:
	rm -rf $(name)