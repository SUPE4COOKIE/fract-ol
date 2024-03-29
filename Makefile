CFLAGS = -MMD -MP # -Wall -Wextra -Werror
NAME = fractol

SRC_PATH = src
SRC_FILES = main.c ft_atoi.c
SRCS = $(addprefix $(SRC_PATH)/, $(SRC_FILES))
OBJ = $(SRCS:.c=.o)
OBJDEPS = $(OBJ:.o=.d)

MLX_PATH = minilibx-linux
MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJ)
	cc $(OBJ) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	cc $(CFLAGS) -I$(MLX_PATH) -c $< -o $@

-include $(OBJDEPS)

clean:
	rm -f $(OBJ) $(OBJDEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re