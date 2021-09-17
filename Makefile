
NAME			=	minishell

CFLAGS			=	-Wall -Wextra -Werror -g

RFLAGS			=	-lreadline

RARMFLAG		=	-ltermcap

DIR_LIBFT		=	libft

DIR_SRCS		=	srcs

DIR_INCLUDE		=	./includes

DIR_RLN_LIB		=	./readline

DIR_UTILS		=	$(DIR_SRCS)/utils
DIR_MAIN_RT		=	$(DIR_SRCS)/main_routine
DIR_EXECUTOR	=	$(DIR_SRCS)/executor

SRCS			=	$(DIR_MAIN_RT)/minishell.c \
					$(DIR_MAIN_RT)/checks.c	\
					$(DIR_MAIN_RT)/signals.c \
					$(DIR_MAIN_RT)/main_loop.c \
					$(DIR_MAIN_RT)/lexer.c \
					$(DIR_MAIN_RT)/lexer_checks.c \
					$(DIR_MAIN_RT)/parser.c \
					$(DIR_MAIN_RT)/pipes.c \
					$(DIR_MAIN_RT)/redirects.c \
					$(DIR_MAIN_RT)/redirect_list.c \
					$(DIR_MAIN_RT)/choose_executor.c

UTILS			=	$(DIR_UTILS)/inits.c \
					$(DIR_UTILS)/free_all.c \
					$(DIR_UTILS)/free_all_2.c \
					$(DIR_UTILS)/envp_list.c \
					$(DIR_UTILS)/envp_list_2.c \
					$(DIR_UTILS)/envp_list_3.c \
					$(DIR_UTILS)/raw_list.c \
					$(DIR_UTILS)/treated_list.c \
					$(DIR_UTILS)/error.c \
					$(DIR_UTILS)/libft_more.c \
					$(DIR_UTILS)/libft_more_2.c

MY_FUNCTION		=	$(DIR_EXECUTOR)/my_echo.c \
					$(DIR_EXECUTOR)/my_pwd.c \
					$(DIR_EXECUTOR)/my_env.c \
					$(DIR_EXECUTOR)/my_cd.c \
					$(DIR_EXECUTOR)/my_exit.c \
					$(DIR_EXECUTOR)/my_nondefault.c \
					$(DIR_EXECUTOR)/my_nondef_pipe.c \
					$(DIR_EXECUTOR)/my_unset.c \
					$(DIR_EXECUTOR)/my_export_more.c \
					$(DIR_EXECUTOR)/my_export.c

HEADERS			=	$(DIR_INCLUDE)/minishell.h \
					$(DIR_INCLUDE)/structures.h \
					$(DIR_INCLUDE)/defines.h \
					$(DIR_INCLUDE)/envp.h \
					$(DIR_INCLUDE)/treated_list.h \
					$(DIR_INCLUDE)/libft_more.h \
					$(DIR_INCLUDE)/raw.h \
					$(DIR_INCLUDE)/redirect.h \
					$(DIR_LIBFT)/libft.h

OBJSDIR			=	temporary

OBJS			=	$(subst ${DIR_MAIN_RT}/, $(OBJSDIR)/, $(SRCS:.c=.o)) \
					$(subst ${DIR_UTILS}/, $(OBJSDIR)/, $(UTILS:.c=.o)) \
					$(subst ${DIR_EXECUTOR}/, $(OBJSDIR)/, $(MY_FUNCTION:.c=.o))

INCLUDES		=	-I ./includes

INCLUDES_LIBFT	=	-I ./libft

INCLUDES_RLN	=	-I ./readline_lib


L_LIBFT			=  ./libft/libft.a

L_READLINE_LIB	=  $(DIR_RLN_LIB)/libhistory.a $(DIR_RLN_LIB)/libreadline.a

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
	@gcc $(CFLAGS)  $(INCLUDES) $(INCLUDES_LIBFT)  -c $< -o $@

$(OBJSDIR)/%.o: $(DIR_UTILS)/%.c | $(OBJSDIR)
	@gcc $(CFLAGS)  $(INCLUDES) $(INCLUDES_LIBFT)  -c $< -o $@

$(OBJSDIR)/%.o: $(DIR_EXECUTOR)/%.c | $(OBJSDIR)
	@gcc $(CFLAGS) $(INCLUDES) $(INCLUDES_LIBFT)   -c $< -o $@

$(NAME): $(OBJS) $(HEADERS)
	@echo "${MAGENTA} ${WORD_MINISHELL}${NORMAL}"
	@echo "${YELLOW} ${WORD_LOADING}${NORMAL}"
	@make -C ./${DIR_LIBFT}
	@gcc $(CFLAGS) $(INCLUDES) $(INCLUDES_LIBFT) $(INCLUDES_RLN) $(L_READLINE_LIB) $(RARMFLAG)  ${L_LIBFT} $(OBJS) $(OBJS_UTILS) -o $@
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