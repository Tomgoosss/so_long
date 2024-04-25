NAME    := so_long
CFLAGS = -Wunreachable-code -Ofast -Wall -Wextra -Werror -fsanitize=address
LIBMLX  := ./MLX42
GLFW_PATH := /opt/homebrew/lib
LIBFT := ./libft

HEADERS := -I./include -I$(LIBMLX)/include -I$(LIBFT)
LIBS    := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm $(LIBFT)/libft.a -fsanitize=address
SRCS    := main.c map.c movecollect.c  #$(shell find ./src -iname "*.c")
OBJS    := ${SRCS:.c=.o}

all: libmlx libft $(NAME)

libft:
	@make -C $(LIBFT)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) -L$(GLFW_PATH)

clean:
	@rm -rf $(OBJS)
	@make clean -C $(LIBFT)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re libmlx libft