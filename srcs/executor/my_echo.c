#include "minishell.h"

int my_echo(t_raw *root)
{
	t_trls *list;

	list = root->treated_comnd;
	if (root->flags == NULL && list == NULL)
	{
		printf("\n");
		return (0);
	}
	if (root->flags != NULL && ft_strncmp(root->flags, "-n", 3) == 0)
	{
		while (list != NULL)
		{
			if (list->arg)
				printf("%s", list->arg);
			if (list->next != NULL)
				printf(" ");
			list = list->next;
		}
		printf("%%\n");
	}
	else
	{
		while (list != NULL)
		{
			if (list->arg)
				printf("%s", list->arg);
			if (list->next != NULL)
				printf(" ");
			list = list->next;
		}
		printf("\n");
	}
	return (0);
}