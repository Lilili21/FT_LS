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

NAME = ls

SRC = fimain.c extra.c flags.c lists.c sort_merge.c sort_merge_q.c \
    sort_merge_err.c parse_data.c help_parse.c print_data.c help_print.c
SRCDIR = src
SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJ = $(SRC:.c=.o)
OBJDIR = objs
LIB_OBJS = $(addprefix $(OBJDIR)/, $(LIB_OBJ))

all: $(NAME)

$(NAME):
	@make -C libft
	@gcc -Wall -Wextra -Werror -I libft/includes -I includes -c $(SRCS)
	@gcc -o $(NAME) -g $(OBJ) -L libft -lft
	@mkdir -p $(OBJDIR);
	@mv $(OBJ) $(OBJDIR)/

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -rf $(NAME)
	@make -C libft fclean

re: fclean all
