# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gfoote <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/01 18:06:42 by gfoote            #+#    #+#              #
#    Updated: 2019/08/01 18:08:21 by gfoote           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = fimain.c extra.c flags.c lists.c sort_merge.c sort_merge_q.c \
    sort_merge_err.c parse_data.c help_parse.c print_data.c help_print.c \
    help_print2.c help_print3.c help_print4.c
SRCDIR = src
SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJ = $(SRC:.c=.o)
OBJDIR = objs
OBJS = $(addprefix $(OBJDIR)/, $(OBJ))

all: $(NAME)

$(NAME):
	@make -C libft
	@gcc -Wall -Wextra -Werror -I libft/includes -I includes -g -c $(SRCS)
	@gcc -g $(OBJ) -o $(NAME) -L libft -lft
	#@mkdir -p $(OBJDIR);
	#@mv $(OBJ) $(OBJDIR)/

clean:
	@/bin/rm -f $(OBJ)
	@make -C libft clean

fclean: clean
	@/bin/rm -rf $(NAME)
	@make -C libft fclean

re: fclean all
	#@/bin/rm -rf $(OBJDIR)