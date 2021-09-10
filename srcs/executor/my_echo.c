#include "minishell.h"

int my_echo(char **str_mass)
{
	int i;
	if (str_mass[1] == NULL)
		printf("\n");
	if (ft_strncmp(str_mass[1], "-n", 3) == 0)
	{
		i = 2;
		while (str_mass[i] != NULL)
		{
			printf("%s", str_mass[i]);
			if (str_mass[i + 1] != NULL)
				printf(" ");
			i++;
		}
	}
	else
	{
		i = 1;
		while (str_mass[i] != NULL)
		{
			printf("%s", str_mass[i]);
			if (str_mass[i + 1] != NULL)
				printf(" ");
			i++;
		}
		printf("\n");
	}
	return (0);
}