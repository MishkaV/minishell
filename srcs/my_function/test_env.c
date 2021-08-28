#include "minishell.h"

int		main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_vars vars;
	char **str_mass;

	init_envp(&vars, envp);
	str_mass = malloc(sizeof(char *) * 4);
	str_mass[0] = ft_strdup("env");
	str_mass[1] = ft_strdup("/Users/lsinistr/MiniShell/minishell/srcs/my_function/a.out");
	str_mass[2] = ft_strdup("-P");
	str_mass[3] = NULL;
	my_env(vars, str_mass);
	return (0);
}