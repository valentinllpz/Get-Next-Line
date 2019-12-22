/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:47:19 by vlugand-          #+#    #+#             */
/*   Updated: 2019/12/22 17:44:46 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"												

int		find_index(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != (char)c)
		i++;
	if (s[i] != (char)c)
		return (-1);
	return (i);
}

int		get_line(char **str, char **line, int i)
{
	int		len;

	*line = ft_substr(*str, 0, i);
	++i;
	len = ft_strlen(*str + i) + 1;
	ft_memmove(*str, *str + i, len);
	if (*str && *str[0] == '\0')
	{
		free(*str);
		*str = NULL;
	}
	return (1);
}

int		get_next_line(int fd, char **line)							// The only difference here is 'str[fd]', otherwise it's exactly the same as the code of GNL without bonus.
{
	char			buff[BUFFER_SIZE + 1];
	static char		*str[OPEN_MAX];									// OPEN_MAX is used in <limits.h>, it corresponds to the max fd value. Read more about it on internet.
	int				ret;
	int				i;

	if (!line || fd < 0 || BUFFER_SIZE < 1 || read(fd, buff, 0) < 0)
		return (-1);
	if (str[fd] && (((i = find_index(str[fd], '\n')) != -1)))
		return (get_line(&str[fd], line, i));
	while (((ret = read(fd, buff, BUFFER_SIZE)) > 0))
	{
		buff[ret] = '\0';
		str[fd] = join_and_free(str[fd], buff);
		if (((i = find_index(str[fd], '\n')) != -1))
			return (get_line(&str[fd], line, i));
	}
	if (str[fd])
	{
		*line = ft_strdup(str[fd]);
		free(str[fd]);
		str[fd] = NULL;
		return (ret);
	}
	*line = ft_strdup("");
	return (ret);
}
