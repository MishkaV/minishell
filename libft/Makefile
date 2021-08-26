# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/10 14:00:29 by jbenjy            #+#    #+#              #
#    Updated: 2021/08/26 11:20:45 by jbenjy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c \
						ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c \
						ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c \
						ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
						ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c \
						ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
						ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
						ft_putchar_fd.c  ft_putstr_fd.c ft_putendl_fd.c \
						ft_putnbr_fd.c
						
SRCS_B = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
			ft_lstdelone.c ft_lstclear.c ft_lstmap.c ft_lstiter.c


OBJSDIR			=	temporary

OBJS			=	$(addprefix ${OBJSDIR}/, $(SRCS:.c=.o))
OBJSB			=	$(addprefix ${OBJSDIR}/, $(SRCS_B:.c=.o))

HEADER			=	libft.h
CFLAGS			=	-Wall -Wextra -Werror


RED				=	\033[0;31m
GREEN			=	\033[0;32m
YELLOW			=	\033[0;33m
MAGENTA			=	\033[0;35m
NORMAL			=	\033[0m


WORD_COMILE_LIBFT	=	████─████─█───█─████─███─█───███ \t	█───███─████──███─███\n\
						█──█─█──█─██─██─█──█──█──█───█ \t	█────█──█──██─█────█\n\
						█────█──█─█─█─█─████──█──█───███ \t	█────█──████──███──█\n\
						█──█─█──█─█───█─█─────█──█───█ \t	█────█──█──██─█────█\n\
						████─████─█───█─█────███─███─███ \t	███─███─████──█────█\n

WORD_COMPLETE_LIBFT	=		████─████─█───█─████─█───███─███─███ \t	█───███─████──███─███\n\
							█──█─█──█─██─██─█──█─█───█────█──█ \t	█────█──█──██─█────█\n\
							█────█──█─█─█─█─████─█───███──█──███ \t	█────█──████──███──█\n\
							█──█─█──█─█───█─█────█───█────█──█ \t	█────█──█──██─█────█\n\
							████─████─█───█─█────███─███──█──███ \t	███─███─████──█────█\n

WORD_COMPILE_BONUS	=		████─████─█───█─████─███─█───███ \t	████──████─█──█─█─█─███\n\
							█──█─█──█─██─██─█──█──█──█───█ \t	█──██─█──█─██─█─█─█─█\n\
							█────█──█─█─█─█─████──█──█───███ \t	████──█──█─█─██─█─█─███\n\
							█──█─█──█─█───█─█─────█──█───█ \t	█──██─█──█─█──█─█─█───█\n\
							████─████─█───█─█────███─███─███ \t	████──████─█──█─███─███\n




all:	${NAME}

$(OBJSDIR):
		@mkdir $@

$(OBJSDIR)/%.o: %.c | $(OBJSDIR)
		@gcc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(HEADER)
		@echo "${YELLOW} ${WORD_COMILE_LIBFT}${NORMAL}"
		@ar rcs $(NAME) ${OBJS}
		@echo "${GREEN} ${WORD_COMPLETE_LIBFT}${NORMAL}"

bonus: $(OBJS) $(OBJSB) $(HEADER)
		@echo "${YELLOW} ${WORD_COMPILE_BONUS}${NORMAL}"
		@ar rcs $(NAME) $(OBJS) $(OBJSB)
		@echo "${GREEN} ${WORD_COMPLETE_LIBFT}${NORMAL}"

clean:
		@rm -rf $(OBJSDIR)
		@rm -f $(OBJS) ${OBJSB}

fclean:	clean
		@rm -f ${NAME}

re:		fclean all
