#include "libft.h"
#include "get_next_line.h"
#include <fcntl.h>

int	main(void)
{
	char	*line;
	int	fd;

	fd = open("file.txt", O_RDONLY);
	if (fd < 0)
		return (-1);
	while (get_next_line(fd, &line) > 0)
	{
		write(1, line, ft_strlen(line));
		write(1, "\n", 1);
		free(line);
	}
}
