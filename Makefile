CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = get_next_line.c
OBJS = $(patsubst %.c, %.o, $(SRCS))
LIB = get_next_line.a
LIBFT = libft.a

$(LIB): $(LIBFT) $(OBJS)
	ar rcs $(LIB) $(OBJS)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I libft/includes -L libft/ -lft -I.
$(LIBFT):
	make -C libft/
all: $(LIB)

clean:
	rm -f $(OBJS) *.o
	make -C libft/ clean
fclean: clean
	rm -rf $(LIB) test_gnl
re: fclean all

.PHONY: all clean fclean re
