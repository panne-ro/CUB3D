NAME = cub3D
CC = cc
FLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address
SRC_DIR = ./src
OBJ_DIR = ./objects
SRC = 	$(SRC_DIR)/main.c \
		$(SRC_DIR)/parsing/parsing_arg.c \
		$(SRC_DIR)/parsing/checkmap.c \
		$(SRC_DIR)/parsing/checkContent.c

OBJS = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@


LIBFT_DIR   := ./includes/libft
LIBFT_LIB   := $(LIBFT_DIR)/libft.a
LIBFT_FLAGS := -L$(LIBFT_DIR) -lft
INCLUDES := -I./includes -I./includes/libft

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(OBJS)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBFT_FLAGS)

$(OBJ_DIR):
			@mkdir -p $(OBJ_DIR) 

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
			@rm -rf $(OBJ_DIR)
			@$(MAKE) -C $(LIBFT_DIR) clean

fclean:	clean
			@rm -f $(NAME)
			@rm -f $(LIBFT_LIB)

re: fclean all

.PHONY: all clean fclean re
