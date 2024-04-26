NAME	:= so_long
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast #-g -fsanitize=address
LIBMLX	:= ./MLX42
MLXA := ./MLX42/build/libmlx42.a
LIBFT := ./libft
LIBFT_A = ./libft/libft.a

HEADERS	:= -I ./include -I $(LIBMLX)/include -I$(LIBFT)
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm  $(LIBFT)/libft.a #-fsanitize=address
SRCS	:= main.c map.c movecollect.c #$(shell find ./src -iname "*.c")
OBJS	:= ${SRCS:.c=.o}

all: $(MLXA) $(LIBFT_A) $(NAME)

$(LIBFT_A):
	@make -C $(LIBFT)

$(MLXA):
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
	@make clean -C $(LIBFT)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT)

re: clean all

.PHONY: all, clean, fclean, re, libmlx, libft