# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gfoote <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/01 18:06:42 by gfoote            #+#    #+#              #
#    Updated: 2019/08/28 19:38:16 by gfoote           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = fimain.c extra.c flags.c lists.c sort_merge.c sort_merge_q.c \
    sort_merge_err.c parse_data.c help_parse.c print_data.c help_print.c \
    help_print2.c help_print3.c help_print4.c extra2.c help_parse2.c

SRCDIR = src
SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJ = $(SRC:.c=.o)
OBJDIR = objs
OBJS = $(addprefix $(OBJDIR)/, $(OBJ))

all: $(NAME)

$(NAME):
	@make -C libft
	@gcc -g -Wall -Wextra -Werror -I libft/includes -I includes -c $(SRCS)
	@mkdir -p $(OBJDIR);
	@mv $(OBJ) $(OBJDIR)/
	@gcc -g -L libft -lft $(OBJS) -o $(NAME)

clean:
	@/bin/rm -rf $(OBJ)
	@make -C libft clean

fclean: clean
	@/bin/rm -rf $(NAME)
	@make -C libft fclean

re: fclean all
