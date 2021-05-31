NAME = philo_one
CFLAG = -Wall -Wextra -Werror

SRCS = main.c \
		philo_one.c \
		parse_init.c \
		msg.c \
		utils.c
OBJS = $(SRCS:.c=.o)

INCLUDE = -I ./include

LIBS = -lpthread

$(NAME) : $(OBJS)
	gcc $(CFLAG) -o $@ $(OBJS) $(LIBS) $(INCLUDE)

%.o:%.c
	gcc $(CFLAG) -c $< -o $@ $(INCLUDE)

all : $(NAME)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

run : all
	./philo_one

.PONY : all clean fclean re bonus run
