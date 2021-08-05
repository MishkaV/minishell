# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/03 15:05:44 by jbenjy            #+#    #+#              #
#    Updated: 2021/08/05 19:03:30 by jbenjy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

CFLAGS			=	-Wall -Wextra -Werror

DIR_LIBFT		=	libft

DIR_SRCS		=	srcs

SRCS			=	$(DIR_SRCS)/minishell.c 

OBJSDIR			=	Temporary

OBJS			=	$(subst srcs/, $(OBJSDIR)/, $(SRCS:.c=.o))

INCLUDES		=	-I ./includes

INCLUDES_LIBFT	=	-I ./libft

L_LIBFT			=  ./libft/libft.a

all: $(NAME) 

$(OBJSDIR):
	mkdir $@

$(OBJSDIR)/%.o: $(DIR_SRCS)/%.c | $(OBJSDIR)
	gcc -g $(CFLAGS) $(INCLUDES) $(INCLUDES_LIBFT) -c $< -o $@

$(NAME): $(OBJS)
	make -C ./${DIR_LIBFT}
	gcc -g $(CFLAGS) $(INCLUDES) $(INCLUDES_LIBFT) ${L_LIBFT} $(OBJS) -o $@

clean:
	rm -rf $(OBJSDIR)
	make -C ./libft clean

fclean: clean
	rm -rf $(NAME)
	make -C ./libft fclean

re: fclean all
