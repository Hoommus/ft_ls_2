
NAME = ft_ls

FLAGS = -Wall -Wextra -Werror -g

HEADER = -I include -I ./libft
SRC_DIR = ./src/
OBJ_DIR = ./obj/

LIB_DIR = ./libft
LIB_NAME = libft.a

SRC = main.c \
      permissions.c \
      filelist_print.c \
      filelist_print_one.c \
      fullpath.c \
      filelist.c \
      errors.c \
      filelist_sort.c \
      mem.c \
      flags.c \
      readdir.c

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIB_DIR)
	cp $(LIB_DIR)/$(LIB_NAME) ./$(LIB_NAME)
	clang $(FLAGS) -o $(NAME) $(OBJ) $(HEADER) $(LIB_NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c include/ft_ls.h
	@mkdir -p $(OBJ_DIR)
	clang $(FLAGS) $(HEADER) -o $@ -c $<

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

