ARCHIVE_NAME = fdf.a
PROGRAM_NAME = fdf

CC = gcc

MY_SOURCES = ft_printf/ft_printf.c ft_printf/ft_printf_char.c ft_printf/ft_printf_number.c ft_printf/ft_printf_number_base.c ft_printf/ft_printf_number_unsigned.c ft_printf/ft_printf_pointer.c ft_printf/ft_printf_string.c ft_atoi.c ft_split.c fdf.c cleanup.c draw.c draw3d.c init.c map_utils.c smieci.c hipsometric_colors.c

MY_OBJECTS = $(MY_SOURCES:.c=.o)

CFLAGS = -Wall -Wextra -Werror

FLAGS = -g -Iminilibx-linux -Lminilibx-linux -lmlx -lXext -lX11 -lm -lz

all: $(ARCHIVE_NAME)

$(ARCHIVE_NAME): $(MY_OBJECTS)
	ar rcs $(ARCHIVE_NAME) $(MY_OBJECTS)
	
program: all
	$(CC) $(CFLAGS) $(MY_OBJECTS) $(FLAGS) -o $(PROGRAM_NAME)
	$(MAKE) clean
	
%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@
	
clean:
	rm -f $(MY_OBJECTS)
	
fclean: clean
	rm -f $(ARCHIVE_NAME)
	
re: fclean all

.PHONY: all clean fclean re
