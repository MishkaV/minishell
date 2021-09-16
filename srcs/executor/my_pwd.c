#include "minishell.h"

int	my_pwd(void)
{
	char *str_pwd;

	str_pwd = getcwd(NULL, PWD_BUFF);
	if (str_pwd == NULL)
		exit(errno);
	printf("%s\n", str_pwd);
	free(str_pwd);
	return (0);
}