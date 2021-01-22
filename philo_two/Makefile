NAME= philo_two
SRCS= main.c errors.c data.c utils.c print.c threads.c routine.c semaphores.c philo_loop.c
OBJS= $(addprefix srcs/,$(SRCS:.c=.o))
CC= gcc
CFLAGS= -Wall -Werror -Wextra
HEADER= -I includes

.c.o:
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $(<:.c=.o)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
all: $(NAME)
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re
