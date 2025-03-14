/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 21:33:23 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/14 01:10:55 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

int	ft_strlen_valid(char *str)
{
	int	i;

	i = 0;
	while (isalpha(str[i]))
		i++;
	return(i);
}

char	*ft_replace(char *base, int start, int end, char *in)
{
	char	*dest;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = ft_strlen(base) - (end - start + 1) + ft_strlen(in);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	while (i < start)
	{
		dest[i] = base[i];
		i++;
	}
	dest[i] = '\0';
	while (in && in[j])
		dest[i++] = in[j++];
	j = end + 1;
	dest[i] = '\0';
	while (base[j])
		dest[i++] = base[j++];
	dest[i] = '\0';
	free(base);
	free(in);
	return (dest);
}

char	*ft_return_var_env(char *str, t_env *infos)
{
	int		len;
	char	*name;
	char	*value;

	value = NULL;
	len = 0;
	while (!ft_limite(str[len]))
		len++;
	name = (char *)malloc((len + 1) * sizeof(char));
	name[len] = '\0';
	len--;
	while(len >= 0)
	{
		name[len] = str[len];
		len--;
	}
	value = value_env(name, infos);
	free(name);
	return (value);
}

char	*ft_cvt_var_env(char *str, t_env *infos)
{
	int		i;
	char	*var;
	char	*dest;

	i = 0;
	dest = ft_strdup(str);
	while(dest[i])
	{
		if (dest[i] == '$' && ft_isdigit(dest[i + 1]))
		{
			dest = ft_replace(dest, i, i + 1, NULL);
			i += 2;
		}
		else if (dest[i] == '$' && ft_isalnum(dest[i + 1]))
		{
			i++;
			var = ft_return_var_env(&dest[i], infos);
			dest = ft_replace(dest, i - 1, i - 1 + ft_strlen_valid(&dest[i]), var);
			i += ft_strlen_valid(&dest[i + 1]);
		}
		else if (dest[i] == '$' && dest[i + 1] == '?')
		{
			dest = ft_replace(dest, i, i + 1, ft_itoa(infos->status));
			i += 2;
		}
		else
			i++;
	}
	return(dest);
}
