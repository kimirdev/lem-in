LIB     = libft/
NAME    = lem-in
CFLAGS  = -Wall -Wextra -Werror
CC      = gcc
SRC_DIR	= src/

SRCS    = lemin.c \
			add_level.c \
			ant_and_comment.c \
			check_in.c \
			check_out.c \
			count_in_out.c \
			free.c \
			init.c \
			links.c \
			output.c \
			path.c \
			validate.c \
			move.c
HEADER  = includes/
OBJS    = $(SRCS:.c=.o)
OBJ_DIR = obj/

all: lib $(NAME)

$(NAME): $(OBJ_DIR) $(addprefix $(OBJ_DIR), $(OBJS))
	@gcc $(CFLAGS) $(addprefix $(OBJ_DIR), $(OBJS)) -I $(HEADER) -L libft $(LIB)libft.a -o $(NAME)
	@echo "\033[32mLEM-IN COMPILED\033[0m"

lib:
	@make -C $(LIB)

$(OBJ_DIR):
	mkdir obj

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	gcc $(CFLAGS) -c -I./$(HEADER) $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIB) clean

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIB) fclean

re: fclean all
