NAME = philo

CC = gcc
CCFLAGS = -Wall -Wextra -Werror -o2
LDFLAGS= -lpthread

DIR_H := include
H = philosophers.h
H := $(addprefix $(DIR_H)/, $(H))

DIR_SRC = src
SRC =	main.c \
		parser.c \
		actions.c \
		extra.c \
		extra_thread.c \
		lib.c \
		lib2.c
SRC := $(addprefix $(DIR_SRC)/, $(SRC))

DIR_OBJ = obj
OBJ = $(SRC:%.c=%.o)
OBJ := $(patsubst $(DIR_SRC)/%, $(DIR_OBJ)/%, $(OBJ))

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CCFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)
	@echo "--------------------------------"
	@echo "${NAME} compiled"
	@echo "--------------------------------"

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c $(H)
	@mkdir -p $(dir $@)
	@echo "[$<] ---> [$@]"
	@$(CC) $(CCFLAGS) -I$(DIR_H) -c $< -o $@

clean:
	@rm -rf $(DIR_OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
