/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stars.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/14 18:50:35 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

/*	
	📛 need to free() after using
	
	transfer **this********is*****star**
	=> become *this*is*star*
	transfer **************
	=> become *
*/

// static char	*ft_stars_str(char *s)
// {
// 	char	**split;
// 	char	*new;
// 	char	*temp;

// 	if (!s || !s[0])
// 		return (NULL);
// 	split = ft_split_charset(s, "*");
// 	if (!split)
// 		return (NULL);
// 	new = ft_strjoin_sep(split, "*");
// 	if (!new)
// 		return (NULL);
// 	if (s[0] && s[0] == '*')
// 	{
// 		temp = new;
// 		new = ft_strjoin("*", temp);
// 		free(temp);
// 	}
// 	if (s[ft_strlen(s) - 1] && s[ft_strlen(s) - 1] == '*')
// 	{
// 		temp = new;
// 		new = ft_strjoin("*", temp);
// 		free(temp);
// 	}
// 	return (ft_split_free(split), new);
// }

// static int	only_stars(char *s)
// {
// 	int	i;

// 	if (!s || !s[0])
// 		return (0);
// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] != '*')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// char	*ft_stars(char *s)
// {
// 	if (!s)
// 		return (NULL);
// 	if (only_stars(s) > 0)
// 	{
// 		free(s);
// 		return (ft_strdup("*"));
// 	}
// 	else
// 	{
// 		free(s);
// 		return (ft_stars_str(s));	
// 	}
// }

// #include <stdio.h>
// int	main(void)
// {
// 	char *s = "";
// 	char *new = ft_stars(s);
// 	printf("new: %s\n", new);
// 	free(new);
// 	return (0);
// }