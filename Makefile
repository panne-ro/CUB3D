NAME = cub3D
CC = cc
FLAGS = -Wall -Wextra -Werror
SRC_DIR = ./src
OBJ_DIR = ./objects
SRC = 	$(SRC_DIR)/main.c
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIB = 

all: $(NAME)

$(NAME): $(OBJ)
			$(CC) $(FLAGS) -o $(NAME) $(OBJ)

$(OBJ_DIR):
			mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
			$(CC) $(FLAGS) -c $< -o $@

clean:
			rm -f $(OBJ) | rm -rf $(OBJ_DIR)

fclean:	clean
			rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
