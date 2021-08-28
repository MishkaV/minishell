#include "minishell.h"

int		main()
{
	char **str_mass;
	str_mass = malloc(sizeof(char *) * 2);
	str_mass[0] = ft_strdup("pwd");
	// str_mass[1] = ft_strdup("hello");
	// str_mass[2] = ft_strdup("abc");
	str_mass[1] = NULL;
	my_pwd(str_mass);
	return (0);
}