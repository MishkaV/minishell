# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/03 15:05:44 by jbenjy            #+#    #+#              #
#    Updated: 2021/08/03 16:36:07 by jbenjy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

CFLAGS			=	-Wall -Wextra -Werror

SRCS			=	srcs/minishell.c 

OBJSDIR			=	Temporary

OBJS			=	$(subst srcs/, $(OBJSDIR)/, $(SRCS:.c=.o))

INCLUDES		=	-I./includes

DIR_LIBFT		=	./libft

INCLUDES_LIBFT	=	-I./libft

all: $(NAME) 

# FORCE: 		;

$(LIBFT): 
	make -C ${DIR_LIBFT}

$(OBJSDIR):
	mkdir $@

$(OBJSDIR)/%.o: srcs/%.c | $(OBJSDIR)
# .с.o:
	gcc -g $(CFLAGS) $(INCLUDES) $(INCLUDES_LIBFT) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT) $(INCLUDES)
	gcc -g $(OBJS) $(INCLUDES) $(INCLUDES_LIBFT) -o $@

clean:
	rm -rf $(OBJSDIR)
	make -C ./libft clean

fclean: clean
	rm -rf $(NAME)
	make -C ./libft fclean

re: fclean all
