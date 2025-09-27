#include "get_next_line.h"

static int	line_stashed(char **line, char **stashed)
{
	char	*pos;
	char	*tmp;

	if (!stashed || !*stashed)
		return (-1);
	pos = ft_strchr(*stashed, '\n');
	if (pos)
	{
		*line = ft_strndup(*stashed, (pos - *stashed));
		tmp = ft_strdup(*stashed + (pos - *stashed) + 1);
		free(*stashed);
		*stashed = ft_strdup(tmp);
		free(tmp);
	}
	else if (!pos)
	{
		*line = ft_strdup(*stashed);
		free(*stashed);
		*stashed = ft_strdup("");
	}
	return (1);
}

static int	remaining_stashed(char **line, char **stashed)
{
	if (!stashed || !*stashed)
		return (-1);
	if (ft_strlen(*stashed) >= 1)
		return (line_stashed(line, stashed));
	free(*stashed);
	return (0);
}

static int	get_line_append_buffer(char **line, char **stashed, char *buffer)
{
	char	*pos;
	char	*tmp;

	if (!stashed || !*stashed || !buffer)
		return (-1);
	pos = ft_strchr(*stashed, '\n');
	if (pos)
	{
		*line = ft_strndup(*stashed, (pos - *stashed));
		tmp = ft_strdup(*stashed + (pos - *stashed) + 1);
	}
	else
		tmp = ft_strdup(*stashed);
	free(*stashed);
	*stashed = ft_strnew(sizeof(char) * (ft_strlen(tmp) + ft_strlen(buffer)));
	if (!*stashed)
		return (-1);
	ft_strcpy(*stashed, tmp);
	ft_strcat(*stashed, buffer);
	free (tmp);
	if (pos)
		return (1);
	return (0);
}

static int	get_line_from_buffer(char **line, char **stashed, char *buffer)
{
	int		len_s;
	char	*pos;
	char	*tmp;

	if (!stashed || !*stashed || !buffer)
		return (-1);
	len_s = get_line_append_buffer(line, stashed, buffer);
	if (len_s == 1)
		return (len_s);
	len_s = ft_strlen(*stashed);
	pos = ft_strchr(*stashed, '\n');
	if (pos)
	{
		*line = ft_strnew(sizeof(char) * (pos - *stashed));
		if (!*line)
			return (-1);
		ft_strncpy(*line, *stashed, (pos - *stashed));
		tmp = ft_strdup(*stashed + (pos - *stashed) + 1);
		free(*stashed);
		*stashed = ft_strdup(tmp);
		free(tmp);
		return (1);
	}
	return (0);
}

int	get_next_line(const int fd, char **line)
{
	int			bytes_read;
	char		buffer[BUFF_SIZE + 1];
	static char	*stashed = NULL;

	if (fd < 0 || !line)
		return (-1);
	if (!stashed)
		stashed = ft_strdup("");
	ft_memset(buffer, 0, BUFF_SIZE + 1);
	bytes_read = read(fd, buffer, BUFF_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		if (get_line_from_buffer(line, &stashed, buffer) == 1)
		{
			ft_memset(buffer, 0, BUFF_SIZE + 1);
			return (1);
		}
		ft_memset(buffer, 0, BUFF_SIZE + 1);
		bytes_read = read(fd, buffer, BUFF_SIZE);
	}
	if (bytes_read == -1)
		return (-1);
	else
		return (remaining_stashed(line, &stashed));
}
