SRCS	= main.c

SRCS	+= parsing/utilities.c \
parsing/fileverif.c \
parsing/parsing_utilities.c \
parsing/parsing_utilities2.c \
parsing/parsing.c \
parsing/ft_split.c \
parsing/get_next_line.c \
parsing/print_parsing.c \
parsing/utils.c \
mlx/mlx.c \
mlx/movements.c \
mlx/utils.c \
mlx/mlx_utils.c \

OBJS	= $(SRCS:.c=.o)

NAME	= cub3d

FLAGS	= -Wall -Wextra -Werror

INCLUDE	= -Iincludes -Iminilibx -lz -lmlx -framework OpenGL -framework AppKit

HEADER	= cub3d.h

all:	$(NAME)

.PHONY:	clean fclean re bonus bench bclean

$(NAME): $(OBJS)
	@gcc $(INCLUDE) $(FLAGS) -o $(NAME) $(OBJS)

clean:
	@rm -f $(OBJS) $(B_OBJS)

fclean: clean
	@rm -f $(NAME) $(BONUS)

re: fclean all

run: re
	@./$(NAME) map.cub
	
%.o: %.c $(HEADER)
	@gcc $(FLAGS) -c $<  -o $(<:.c=.o)