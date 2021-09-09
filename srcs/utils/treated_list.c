/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treated_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 11:05:53 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/09 12:30:20 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_trls  *trls_new_node(char *arg)
{
    t_trls *curr;
    
    curr = malloc(sizeof(t_trls));
    if(!curr)
        return (0);
    curr->arg = arg;
    curr->next = 0;
    return (curr);
}

t_trls  *trls_push_node(t_trls *root, char *arg)
{
    t_trls *to_return;

    to_return = root;
    if(!root)
        return (trls_new_node(arg));
    while (root->next)
        root = root->next;
    root->next = trls_new_node(arg);
    return (to_return);
}

int  trls_get_len(t_trls *root)
{
    int len;

    len = 0;
    if (!root)
        return (len);
    while (root)
    {
        len++;
        root = root->next;
    }
    return(len);
}

void    trls_free_list(t_trls *root)
{
    t_trls *next;
    
    if (root)
    {
        while(root)
        {
            next = root->next;
            if (root->arg)
                free(root->arg);
            free(root);
            root = next;
        }    
    }
}

void    trls_print_list(t_trls *root)
{
    if (!root)
        return ;
    while (root)
    {
        printf("Treadted: %s\n", root->arg);
        root = root->next;
    }
}