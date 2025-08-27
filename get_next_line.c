#include "get_next_line.h"

static int	ft_fill_stashed(char **stashed, char *buffer)
{
	int		len_stashed;
	char	*tmp;

	if (!stashed)
		return (-1);
	len_stashed = 0;
	if (*stashed)
		len_stashed = ft_strlen(*stashed);
	tmp = (char *)malloc(sizeof(char) * (len_stashed + ft_strlen(buffer) + 1));
	if (!tmp)
		return (-1);
	if (*stashed)
	{
		tmp = ft_strncpy(tmp, *stashed, ft_strlen(*stashed));
		tmp = ft_strncat(tmp, buffer, ft_strlen(buffer));
	}
	else
		tmp = ft_strncpy(tmp, buffer, ft_strlen(buffer));
	free(*stashed);
	*stashed = tmp;
	ft_memset(buffer, 0, BUFF_SIZE);
	return (1);
}

static int	ft_get_line_from_buffer(char **l, char **stash, char *buf, char *p)
{
	int		len_stashed;

	len_stashed = 0;
	if (*stash)
		len_stashed = ft_strlen(*stash);
	*l = (char *)malloc(sizeof(char) * (len_stashed + (p - buf) + 1));
	if (!*l)
		return (-1);
	if (*stash)
	{
		*l = ft_strncpy(*l, *stash, ft_strlen(*stash));
		*l = ft_strncat(*l, buf, (p - buf));
	}
	else
		*l = ft_strncpy(*l, buf, (p - buf));
	free(*stash);
	*stash = ft_strdup(buf + (p - buf) + 1);
	return (1);
}

static int	ft_get_line_from_stashed(char **line, char **stashed, char *pos)
{
	char	*tmp;

	*line = (char *)malloc(sizeof(char) * (pos - *stashed) + 1);
	if (!*line)
		return (-1);
	*line = ft_strncpy(*line, *stashed, (pos - *stashed));
	tmp = ft_strdup(*stashed + (pos - *stashed) + 1);
	free(*stashed);
	*stashed = ft_strdup(tmp);
	free (tmp);
	return (1);
}

int	get_next_line(const int fd, char **line)
{
	int			bytes_read;
	char		buffer[BUFF_SIZE + 1];
	char		*pos;
	static char	*stashed = NULL;

	if (fd < 0 || !line)
		return (-1);
	if (!stashed)
		stashed = ft_strdup("");
	pos = ft_strchr(stashed, '\n');
	if (pos)
		return (ft_get_line_from_stashed(line, &stashed, pos));
	bytes_read = read(fd, buffer, BUFF_SIZE);
	if (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		pos = ft_strchr(buffer, '\n');
		if (pos)
			return (ft_get_line_from_buffer(line, &stashed, buffer, pos));
		else
			if (ft_fill_stashed(&stashed, buffer) == -1)
				return (-1);
		get_next_line(fd, line);
	}
	return (bytes_read);
}
