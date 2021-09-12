#include "minishell.h"

int	my_pwd(t_raw *root)
{
	char *str_pwd;

	if (root->flags != NULL || root->treated_comnd != NULL)
	{
		ft_putstr_fd("too many arguments\n", STDERR_FILENO);
		return (1);
	}
	str_pwd = getcwd(NULL, PWD_BUFF);
	if (str_pwd == NULL)
		exit(errno);
	printf("%s\n", str_pwd);
	free(str_pwd);
	return (0);
}