NAME = ls

SRC = src/fimain.c \
		src/extra.c \
		src/flags.c \
		src/lists.c \
		src/sort_merge.c \
		src/sort_merge_q.c \
		src/sort_merge_err.c \
		src/parse_data.c \
		src/help_sort.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	make -C libft
	gcc -Wall -I libft/includes -I includes -c $(SRC)
	#gcc -Wall -Wextra -Werror -I libft/includes -I includes -c $(SRC)
	gcc -o $(NAME) $(OBJ) -L libft -lft

clean:
	rm -f $(OBJ)
	#make -C libft clean

fclean: clean
	rm -f $(NAME)
	#make -C libft fclean

re: fclean all
