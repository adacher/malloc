ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
FLAGS = -Wall -Wextra -Werror

SRCS = srcs/malloc.c\
		srcs/display_mem.c\
		srcs/display_utils.c\
		srcs/display_steps.c\
		srcs/libft.c\
		srcs/large_malloc.c\
		srcs/init_malloc.c\
		srcs/custom_malloc.c\
		srcs/free.c\
		srcs/realloc.c\

OBJS = $(SRCS:.c=.o)

INC = -I inc

all: $(NAME)

$(NAME): $(OBJS)
	@gcc -shared -o $(NAME) $(OBJS)
	@ln -sf $(NAME) libft_malloc.so
	@echo "Success"

$(OBJS): %.o:%.c
	@gcc $(FLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f libft_malloc.so

re: fclean all

.PHONY: all clean fclean re