#include "get_next_line.h"
#include "fcntl.h"

int	main()
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	if (fd < 0)
		return -1;
	while (get_next_line(fd, &line) > 0)
	{
		write(1, line, ft_strlen(line));
		write(1, "\n", 1);
	}
	close(fd);
	return (0);
}
