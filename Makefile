
NAME = ft_ls

FLAGS = -Wall -Wextra -Werror

HEADER = include
SRC_DIR = ./src/
OBJ_DIR = ./obj/

LIB_DIR = ./printf
LIB_NAME = libftprintf.a

SRC = main.c

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIB_DIR)
	cp $(LIB_DIR)/$(LIB_NAME) ./$(LIB_NAME)
	clang $(FLAGS) -o $(NAME) $(OBJ) -I $(HEADER) $(LIB_NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(OBJ_DIR)
	clang $(FLAGS) -I $(HEADER) -o $@ -c $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	make -C libft clean
	@echo "rm -rf $(OBJ_DIR)*.o"
	@/bin/rm -rf $(OBJ)
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	make -C $(LIB_DIR) fclean
	/bin/rm -f $(NAME)
	/bin/rm -f $(LIB_NAME)

re: fclean all

