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

OBJ = fimain.o \
		extra.o \
		flags.o \
		lists.o \
		sort_merge.o \
		sort_merge_q.o \
		sort_merge_err.o \
		parse_data.o \
		help_sort.o
#$(SRC:.c=.o)

all: $(NAME)

$(NAME):
	make -C libft
	gcc -g -Wall -I libft/includes -I includes -c $(SRC)
	#gcc -Wall -Wextra -Werror -I libft/includes -I includes -c $(SRC)
	gcc -g -o $(NAME) $(OBJ) -L libft -lft

clean:
	rm -f $(OBJ)
	#make -C libft clean

fclean: clean
	rm -f $(NAME)
	#make -C libft fclean

re: fclean all
