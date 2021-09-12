#include "minishell.h"

int my_echo(t_raw *root)
{
	if (root->flags == NULL && root->treated_comnd == NULL)
	{
		printf("\n");
		return (0);
	}
	if (root->flags != NULL && ft_strncmp(root->flags, "-n", 3) == 0)
	{
		while (root->treated_comnd != NULL)
		{
			printf("%s", root->treated_comnd->arg);
			if (root->treated_comnd->next != NULL)
				printf(" ");
			root->treated_comnd = root->treated_comnd->next;
		}
	}
	else
	{
		while (root->treated_comnd != NULL)
		{
			printf("%s", root->treated_comnd->arg);
			if (root->treated_comnd->next != NULL)
				printf(" ");
			root->treated_comnd = root->treated_comnd->next;
		}
		printf("\n");
	}
	return (0);
}