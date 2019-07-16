NAME = ls

SRC = main.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	make -C libft
	gcc -Wall -Wextra -Werror -I libft/includes -I includes -c $(SRC)
	gcc -o $(NAME) $(OBJ) -L libft -lft

clean:
	rm -f $(OBJ)
	make -C lib clean

fclean: clean
	rm -f $(NAME)
	make -C lib fclean

re: fclean all
