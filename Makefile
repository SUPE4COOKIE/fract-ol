CFLAGS = -MMD -MP -Wall -Wextra -Werror -g3
NAME = fractol

SRC_PATH = src
SRC_FILES = main.c ft_atof.c ft_atof_utils.c hooks.c fractals.c fractals_utils.c args_parser.c
SRCS = $(addprefix $(SRC_PATH)/, $(SRC_FILES))
OBJ = $(SRCS:.c=.o)
OBJDEPS = $(OBJ:.o=.d)

MLX_PATH = minilibx-linux
MLX_A = $(MLX_PATH)/libmlx_Linux.a
MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm

all: $(MLX_A) $(NAME)

$(MLX_A):
	make -C $(MLX_PATH)

$(NAME): $(OBJ) Makefile
	cc $(OBJ) $(MLX_FLAGS) -o $(NAME)

%.o: %.c Makefile
	cc $(CFLAGS) -I$(MLX_PATH) -c $< -o $@

-include $(OBJDEPS)

clean:
	rm -f $(OBJ) $(OBJDEPS)
	make -C $(MLX_PATH) clean

fclean: clean
	rm -f $(NAME)
	make -C $(MLX_PATH) clean

re: fclean all

.PHONY: all clean fclean re