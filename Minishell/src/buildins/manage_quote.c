/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:39:22 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/15 12:33:39 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

char	*ft_quote_clear(char *str)
{
	int		len;
	char	*dest;
	int		i;
	int		j;

	i = 1;
	j = 0;
	len = ft_strlen(str) - 2;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	while (str[i + 1])
	{
		dest[j] = str[i];
		j++;
		i++;
	}
	dest[j] = '\0';
	free(str);
	return(dest);
}

char	*ft_cvt_cmd_on(char *str)
{
	char	*ptr;

	ptr = ft_strdup(str);
	if (str[0] == '\"' || str[0] == '\'')
		ptr = ft_quote_clear(ptr);
	return (ptr);
}

char	**ft_convert_cmd(char **str, t_env *infos)
{
	int		i;

	i = 0;
	while(str[i])
	{
		// if ((!(str[i][0] == '\"') && !(str[i][0] == '\'')) && ft_check_star(str[i]))
		// 	str[i] = ft_replace_cmd_only(str[i]);
		if (!(str[i][0] == '\''))
			str[i] = ft_cvt_var_env(str[i], infos);
		if (str[i][0] == '\"' || str[i][0] == '\'')
			str[i] = ft_quote_clear(str[i]);
		if (!str[i + 1] && !str[i][0])
			str[i] = NULL;	
		i++;
	}
	return (str);
}
