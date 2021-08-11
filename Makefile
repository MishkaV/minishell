# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/03 15:05:44 by jbenjy            #+#    #+#              #
#    Updated: 2021/08/11 15:31:47 by jbenjy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

CFLAGS			=	-Wall -Wextra -Werror -g

RFLAGS			=	-lreadline

DIR_LIBFT		=	libft

DIR_SRCS		=	srcs

DIR_INCLUDE		=	includes

SRCS			=	$(DIR_SRCS)/minishell.c \
					$(DIR_SRCS)/main_loop.c
 
HEADERS			=	$(DIR_INCLUDE)/minishell.h

OBJSDIR			=	temporary

OBJS			=	$(subst ${DIR_SRCS}/, $(OBJSDIR)/, $(SRCS:.c=.o))

INCLUDES		=	-I ./includes

INCLUDES_LIBFT	=	-I ./libft

L_LIBFT			=  ./libft/libft.a

all: $(NAME) 

$(OBJSDIR):
	mkdir $@

$(OBJSDIR)/%.o: $(DIR_SRCS)/%.c | $(OBJSDIR)
	gcc $(CFLAGS) $(INCLUDES) $(INCLUDES_LIBFT) -c $< -o $@

$(NAME): $(OBJS) $(HEADERS)
	make -C ./${DIR_LIBFT}
	gcc $(RFLAGS) $(CFLAGS) $(INCLUDES) $(INCLUDES_LIBFT) ${L_LIBFT} $(OBJS) -o $@

clean:
	rm -rf $(OBJSDIR)
	make -C ./libft clean

fclean: clean
	rm -rf $(NAME)
	make -C ./libft fclean

re: fclean all
