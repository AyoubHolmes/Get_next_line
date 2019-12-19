/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulbaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 22:38:57 by aboulbaz          #+#    #+#             */
/*   Updated: 2019/11/27 16:28:27 by aboulbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	extractor(char **buf, char **line, char *new_line)
{
	char *tmp;

	*line = ft_substr(*buf, 0, new_line - *buf);
	tmp = *buf;
	*buf = ft_substr(*buf, new_line - *buf + 1, BUFFER_SIZE);
	free(tmp);
	return (1);
}

static int	second_case(char **tmp, char **buf, char **line)
{
	free(*tmp);
	if (*buf && **buf != '\0')
	{
		*line = ft_substr(*buf, 0, BUFFER_SIZE);
		free(*buf);
		*buf = 0;
		return (1);
	}
	free(*buf);
	*buf = 0;
	return (0);
}

static int	false_case(char **buf, char **tmp)
{
	free(*tmp);
	free(*buf);
	*buf = 0;
	return (-1);
}

int			get_next_line(int fd, char **line)
{
	static char		*buf;
	char			*tmp;
	char			*p;
	char			*new_line;
	int				i;

	if (BUFFER_SIZE < 0 || !line)
		return (-1);
	if ((new_line = ft_strchr(buf, '\n')))
		return (extractor(&buf, line, new_line));
	if (!(tmp = (char*)malloc(BUFFER_SIZE + 1)))
		return (-1);
	if ((i = read(fd, tmp, BUFFER_SIZE)) > 0)
	{
		tmp[i] = 0;
		p = buf;
		buf = ft_strjoin(buf, tmp);
		free(p);
		free(tmp);
		return (get_next_line(fd, line));
	}
	if (i == 0)
		return (second_case(&tmp, &buf, line));
	return (false_case(&buf, &tmp));
}
