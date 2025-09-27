#include "get_next_line.h"
#include <stdio.h>

static int	get_line_from_buffer(char **line, char **stashed, char *buffer)
{
	int		len_s;
	char	*pos;
	char	*tmp;

	if (!stashed || !*stashed || !buffer)
		return (-1);

	// check stashed first!
	pos = ft_strchr(*stashed, '\n');
	if (pos)
	{
		(void)len_s;
		*line = ft_strndup(*stashed, (pos - *stashed));
		tmp = ft_strdup(*stashed + (pos - *stashed) + 1);
		free(*stashed);
		*stashed = ft_strnew(sizeof(char) * (ft_strlen(tmp) + ft_strlen(buffer)));
		if (!*stashed)
			return (-1);
		ft_strcpy(*stashed, tmp);
		ft_strcat(*stashed, buffer);
		free (tmp);
		return (1);
	}
	else
	{
		tmp = ft_strdup(*stashed);
		free(*stashed);
		*stashed = ft_strnew(sizeof(char) * (ft_strlen(tmp) + ft_strlen(buffer)));
		if (!stashed)
			return (-1);
		ft_strcpy(*stashed, tmp);
		ft_strcat(*stashed, buffer);
		free(tmp);
	}
	
	// get line buffer now!
	len_s = ft_strlen(*stashed);
	pos = ft_strchr(*stashed, '\n');
	if (pos)
	{
		*line = (char *)ft_strnew(sizeof(char) * (pos - *stashed));
		if (!*line)
			return (-1);
		ft_strncpy(*line, *stashed, (pos - *stashed));
		tmp = ft_strdup(*stashed + (pos - *stashed) + 1);
		free(*stashed);
		*stashed = ft_strdup(tmp);
		free(tmp);
		return (1);
	}
	// no lines let stashed before in &stashed stashed everything!
	return (0);
}

int	get_next_line(const int fd, char **line)
{
	int			bytes_read;
	char		buffer[BUFF_SIZE + 1];
	char		*pos, *tmp;
	static char	*stashed = NULL;

	if (fd < 0 || !line)
		return (-1);
	if (!stashed)
		stashed = ft_strdup("");
	ft_memset(buffer, 0, BUFF_SIZE + 1);

	// reading
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
	else if (bytes_read == 0)
	{
		if (ft_strlen(stashed) >= 1)
		{
			pos = ft_strchr(stashed, '\n');
			if (pos)
			{
				*line = ft_strndup(stashed, (pos - stashed));
				tmp = ft_strdup(stashed + (pos - stashed) + 1);
				free(stashed);
				stashed = ft_strdup(tmp);
				free(tmp);
			}
			else
			{
				*line = ft_strdup(stashed);
				free(stashed);   /// look foor
				stashed = ft_strdup("");
			}
			return (1);
		}
		else
		{
			free(stashed);
			return (0);
		}
	}
	return (ft_strlen(*line));
}
