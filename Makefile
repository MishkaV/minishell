# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsinistr <lsinistr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/03 15:05:44 by jbenjy            #+#    #+#              #
#    Updated: 2021/08/27 20:05:05 by lsinistr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

CFLAGS			=	-Wall -Wextra -Werror -g

RFLAGS			=	-lreadline

DIR_LIBFT		=	libft

DIR_SRCS		=	srcs

DIR_INCLUDE		=	includes

DIR_UTILS		=	$(DIR_SRCS)/utils
DIR_MAIN_RT		=	$(DIR_SRCS)/main_routine
DIR_MY_FUNCTION =	$(DIR_SRCS)/my_function

SRCS			=	$(DIR_MAIN_RT)/minishell.c \
					$(DIR_MAIN_RT)/main_loop.c

UTILS			=	$(DIR_UTILS)/inits.c \
					$(DIR_UTILS)/free_all.c \
					$(DIR_UTILS)/envp_list.c \
					$(DIR_UTILS)/libft_more.c

MY_FUNCTION		=	$(DIR_MY_FUNCTION)/my_echo.c \
					$(DIR_MY_FUNCTION)/my_pwd.c \
					$(DIR_MY_FUNCTION)/my_env.c

HEADERS			=	$(DIR_INCLUDE)/minishell.h \
					$(DIR_INCLUDE)/structures.h \
					$(DIR_LIBFT)/libft.h \

OBJSDIR			=	temporary

OBJS			=	$(subst ${DIR_MAIN_RT}/, $(OBJSDIR)/, $(SRCS:.c=.o)) \
					$(subst ${DIR_UTILS}/, $(OBJSDIR)/, $(UTILS:.c=.o)) \
					$(subst ${DIR_MY_FUNCTION}/, $(OBJSDIR)/, $(UTILS:.c=.o))

INCLUDES		=	-I ./includes

INCLUDES_LIBFT	=	-I ./libft

L_LIBFT			=  ./libft/libft.a

RED				=	\033[0;31m
GREEN			=	\033[0;32m
YELLOW			=	\033[0;33m
MAGENTA			=	\033[0;35m
NORMAL			=	\033[0m

WORD_MINISHELL	=	█───█─███─█──█─███─███─█──█─███─█───█\n\
					██─██──█──██─█──█──█───█──█─█───█───█\n\
					█─█─█──█──█─██──█──███─████─███─█───█\n\
					█───█──█──█──█──█────█─█──█─█───█───█\n\
					█───█─███─█──█─███─███─█──█─███─███─███\n

WORD_COMPLETE	=	████─████─█───█─████─█───███─███─███\n\
					█──█─█──█─██─██─█──█─█───█────█──█\n\
					█────█──█─█─█─█─████─█───███──█──███\n\
					█──█─█──█─█───█─█────█───█────█──█\n\
					████─████─█───█─█────███─███──█──███\n

WORD_COMPl_MIN	=	████─████─█───█─████─█───███─███─███ \t	█───█─███─█──█─███─███─█──█─███─█───█\n\
					█──█─█──█─██─██─█──█─█───█────█──█ \t	██─██──█──██─█──█──█───█──█─█───█───█\n\
					█────█──█─█─█─█─████─█───███──█──███ \t	█─█─█──█──█─██──█──███─████─███─█───█\n\
					█──█─█──█─█───█─█────█───█────█──█ \t	█───█──█──█──█──█────█─█──█─█───█───█\n\
					████─████─█───█─█────███─███──█──███ \t	█───█─███─█──█─███─███─█──█─███─███─███\n

WORD_LOADING	=	█───████─████─████──███─█──█─████\n\
					█───█──█─█──█─█──██──█──██─█─█\n\
					█───█──█─████─█──██──█──█─██─█─██\n\
					█───█──█─█──█─█──██──█──█──█─█──█\n\
					███─████─█──█─████──███─█──█─████─█─█─█\n

WORD_CLEANING	=	████─█───███─████─█──█─███─█──█─███─████\n\
					█──█─█───█───█──█─██─█──█──██─█──█──█\n\
					█────█───███─████─█─██──█──█─██──█──█─██\n\
					█──█─█───█───█──█─█──█──█──█──█──█──█──█\n\
					████─███─███─█──█─█──█─███─█──█─███─████─█─█─█\n

WORD_FCLEANING	=	███─████─█───███─████─█──█─███─█──█─███─████\n\
					█───█──█─█───█───█──█─██─█──█──██─█──█──█\n\
					███─█────█───███─████─█─██──█──█─██──█──█─██\n\
					█───█──█─█───█───█──█─█──█──█──█──█──█──█──█\n\
					█───████─███─███─█──█─█──█─███─█──█─███─████─█─█─█\n

WORD_SUCCESS	=	███─█─█─████─████─███─███─███─█\n\
					█───█─█─█──█─█──█─█───█───█───█\n\
					███─█─█─█────█────███─███─███─█\n\
					──█─█─█─█──█─█──█─█─────█───█\n\
					███─███─████─████─███─███─███─█\n


all: $(NAME)

$(OBJSDIR):
	@mkdir $@

$(OBJSDIR)/%.o: $(DIR_MAIN_RT)/%.c | $(OBJSDIR)
	@gcc $(CFLAGS) $(INCLUDES) $(INCLUDES_LIBFT) -c $< -o $@

$(OBJSDIR)/%.o: $(DIR_UTILS)/%.c | $(OBJSDIR)
	@gcc $(CFLAGS) $(INCLUDES) $(INCLUDES_LIBFT) -c $< -o $@

$(OBJSDIR)/%.o: $(DIR_MY_FUNCTION)/%.c | $(OBJSDIR)
	@gcc $(CFLAGS) $(INCLUDES) $(INCLUDES_LIBFT) -c $< -o $@

$(NAME): $(OBJS) $(OBJS_UTILS) $(HEADERS)
	@echo "${MAGENTA} ${WORD_MINISHELL}${NORMAL}"
	@echo "${YELLOW} ${WORD_LOADING}${NORMAL}"
	@make -C ./${DIR_LIBFT}
	@gcc $(RFLAGS) $(CFLAGS) $(INCLUDES) $(INCLUDES_LIBFT) ${L_LIBFT} $(OBJS) $(OBJS_UTILS) -o $@
	@echo "${GREEN} ${WORD_COMPl_MIN}${NORMAL}"



clean:
	@echo "${YELLOW} ${WORD_CLEANING}${NORMAL}"
	@rm -rf $(OBJSDIR)
	@make -C ./libft clean
	@echo "${GREEN} ${WORD_COMPLETE}${NORMAL}"

fclean: clean
	@echo "${YELLOW} ${WORD_FCLEANING}${NORMAL}"
	@rm -rf $(NAME)
	@make -C ./libft fclean
	@echo "${GREEN} ${WORD_SUCCESS}${NORMAL}"

re: fclean all
