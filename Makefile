NAME = cub3D
CC = cc
FLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
SRC_DIR = ./src
OBJ_DIR = ./objects
SRC = 	$(SRC_DIR)/main.c \
		$(SRC_DIR)/parsing_arg.c
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIBFT_DIR   := ./includes/libft
LIBFT_LIB   := $(LIBFT_DIR)/libft.a
LIBFT_FLAGS := -L$(LIBFT_DIR) -lft
INCLUDES := -I./includes -I./includes/libft

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(OBJ)
			$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT_FLAGS)

$(OBJ_DIR):
			mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
			$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@ 

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

clean:
			rm -f $(OBJ) | rm -rf $(OBJ_DIR)
			$(MAKE) -C $(LIBFT_DIR) clean

fclean:	clean
			rm -f $(NAME)
			rm -f $(LIBFT_LIB)

re: fclean all

.PHONY: all clean fclean re
