NAME = cub3D

CC = cc

# CFLAGS = -Wall -Werror -Wextra -g
# CFLAGS = -fsanitize=address
OBJ_DIR = obj/
SRC_DIR = src/

SRC := main.c error.c parse.c parse_color.c get_next_line.c get_next_line_utils.c parse_path.c parse_utils.c parse_map.c render.c hooks.c\

SRCS = $(addprefix $(SRC_DIR), $(SRC))
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_DIR), $(OBJ))
HEADER = -I ./include -I ./lib/MLX42/include/MLX42/

LIBFT = ./libft/libft.a

LIBMLX42 = "./lib/MLX42/build/libmlx42.a"

LDFLAGS := -ldl -lglfw -pthread -lm -flto -framework Cocoa -framework OpenGL -framework IOKit

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) -c $< -o $@ $(HEADER) $(CFLAGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	cd libft && make
	mkdir lib && cd lib && git clone https://github.com/codam-coding-college/MLX42.git
	cd lib/MLX42 && cmake -B build && cmake --build build -j4

install_brew:
	@echo "---- installing brew ----"
	rm -rf $HOME/.brew && rm -rf $HOME/goinfre/.brew && \
	git clone --depth=1 https://github.com/Homebrew/brew $HOME/goinfre/.brew && \
	echo 'export PATH=$HOME/goinfre/.brew/bin:$PATH' >> $HOME/.zshrc && \
	source $HOME/.zshrc && brew update

install_glfw:
	@echo "---- installing glfw ----"
	brew install glfw

install: install_brew install_glfw

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBMLX42) $(HEADER) $(LDFLAGS) -o $(NAME)

clean:
	cd libft && make clean
	rm -rf $(OBJ_DIR)
	rm -rf ./lib

fclean: clean
	cd libft && make fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re