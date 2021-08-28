#include "minishell.h"

int		main()
{
	char **str_mass;
	str_mass = malloc(sizeof(char *) * 4);
	str_mass[0] = ft_strdup("echo");
	str_mass[1] = ft_strdup("hello");
	str_mass[2] = ft_strdup("abc");
	str_mass[3] = NULL;
	my_echo(str_mass);
	return (0);
}