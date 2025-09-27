#include "get_next_line.h"


static int	get_line_from_buffer(char **line, char **stashed, char *buffer)
{
	int		len_stashed;
	char	*pos;

	len_stashed = 0;
	if (*stashed)
		len_stashed = ft_strlen(*stashed);
	pos = ft_strchr(buffer, '\n');
	if (pos)
		*line = (char *)ft_strnew(sizeof(char) * (len_stashed + (pos - buffer)));
	else
		*line = (char *)ft_strnew(sizeof(char) * (len_stashed + ft_strlen(buffer)));
	if (!*line)
		return (-1);
	if (*stashed)
	{
		ft_strncpy(*line, *stashed, ft_strlen(*stashed));
		free(*stashed);
		*stashed = NULL;
	}
	if (pos)
	{
		ft_strncat(*line, buffer, (pos - buffer));
		*stashed = ft_strdup(buffer + (pos - buffer) + 1);
		return (1);
	}
	else
	{
		ft_strncat(*line, buffer, ft_strlen(buffer));
		*stashed = ft_strdup(*line);
		free(*line);
		return (0);
	}
}

static int	get_line_from_stashed(char **line, char *stashed, char *pos)
{
	char	*tmp;

	if (!line || !*line || !pos || !stashed)
		return (-1);
	*line = ft_strndup(stashed, (pos - stashed));
	tmp = ft_strdup(stashed + (pos - stashed) + 1);
	free(stashed);
	stashed = ft_strdup(tmp);
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
		return (get_line_from_stashed(line, stashed, pos));
	ft_memset(buffer, 0, BUFF_SIZE + 1);
	while ((bytes_read = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[bytes_read] = '\0';
		if (get_line_from_buffer(line, &stashed, buffer) == 1)
		{
			ft_memset(buffer, 0, BUFF_SIZE + 1);
			return (1);
		}
		ft_memset(buffer, 0, BUFF_SIZE + 1);
	}
	if (stashed)
	{
		*line = ft_strdup(stashed);
		free(stashed);
		stashed = NULL;
	}
	else
		return (0);
	return (ft_strlen(*line));
}
