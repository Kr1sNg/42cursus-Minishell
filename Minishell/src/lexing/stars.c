/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/13 22:19:10 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

/*	
	transfer **this********is*****star**
	become *this*is*star*
*/

int	ft_lenstrs(int size, char **strs, char *sep)
{
	int	i;
	int	length;

	i = 0;
	length = 0;
	while (i < size)
	{
		length = length + ft_strlen(strs[i]);
		i++;
	}
	length = length + ft_strlen(sep) * (size - 1);
	return (length);
}

char	*ft_strjoin_s(int size, char **strs, char *sep)
{
	char	*strfinal;
	int		n;

	if (size == 0)
	{
		strfinal = malloc(1);
		strfinal[0] = '\0';
		return (strfinal);
	}
	strfinal = malloc(ft_lenstrs(size, strs, sep) + 1);
	if (strfinal == NULL)
		return (0);
	strfinal[0] = '\0';
	n = 0;
	while (n < size)
	{
		ft_strcat(strfinal, strs[n]);
		if (n < size - 1)
			ft_strcat(strfinal, sep);
		n++;
	}
	return (strfinal);
}

int	main(void)
{
	char *s = "**this********is*****star**";

	int s_len = ft_strlen(s);
	int count_word = 3;
	char **split = ft_split_charset(s, "*");
	
	char *new = ft_strjoin_s(count_word, split, "*");

	if (s != NULL && s[0] && s[0] == '*')
		new = ft_strjoin("*", new);
	if (s != NULL && s[s_len - 1] && s[s_len - 1] == '*')
		new = ft_strjoin(new, "*");
	printf("new: %s\n", new);
	free(new);
	ft_split_free(split);
}