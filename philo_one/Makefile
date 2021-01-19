NAME= philo_one
SRCS= main.c data.c ft_atoi.c ft_isspace.c ft_isnum.c ft_isdigit.c errors.c philo_loop.c \
	threads.c routine.c mutex.c print.c
OBJS= $(addprefix srcs/,$(SRCS:.c=.o))
CC= gcc
CFLAGS=
HEADER= -I includes
LIBS= -lpthread

.c.o:
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $(<:.c=.o)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)
all: $(NAME)
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re
