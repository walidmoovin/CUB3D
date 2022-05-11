SRCS	= main.c

SRCS	+= PARSING/utilities.c \
PARSING/fileverif.c \
PARSING/parsing_utilities.c \
PARSING/parsing_utilities2.c \
PARSING/parsing.c \
PARSING/ft_split.c \
PARSING/gnl/get_next_line.c \
PARSING/gnl/get_next_line_utils.c \
PARSING/print_parsing.c \
mlx/mlx.c \
mlx/movements.c \
mlx/utils.c \
mlx/mlx_2.c

OBJS	= $(SRCS:.c=.o)

NAME	= cub3d

FLAGS	= -Wall -Wextra -Werror -fsanitize=address -g

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