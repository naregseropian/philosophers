NAME	:= philo
CC	:= cc -Wall -Wextra -Werror #-g #-fsanitize=thread
SRCS	:= main.c error_handling.c check_args.c init.c actions.c routine.c utils.c end_simulation.c

OBJS	:= $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
