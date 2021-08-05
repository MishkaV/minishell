/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 12:13:40 by jbenjy            #+#    #+#             */
/*   Updated: 2020/11/05 13:08:36 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	const char *chr;

	chr = 0;
	while (*s)
	{
		if (*s == c)
			chr = s;
		s++;
	}
	if (*s == c && c == '\0')
		chr = s;
	if (chr)
		return ((char*)chr);
	else
		return (0);
}
