ARCHIVE_NAME = fdf.a
PROGRAM_NAME = fdf

CC = gcc

MY_SOURCES = ft_atoi.c ft_split.c fdf.c cleanup.c draw3d.c actions.c mouse_actions.c set_hipcometric_color.c keys_actions.c init.c map_utils.c hipsometric_colors.c moon_colors.c offsets.c surface_utils.c objects_utils.c init_object.c ft_ftoa.c ft_strjoin.c ft_atoi_hex.c helpers_bresenham.c bresenham.c lerp_color.c line_print.c iterate_quad.c paint_helpers.c print_utils.c iterate_quad_utils.c colors.c strings.c free_ftoa.c

MY_OBJECTS = $(MY_SOURCES:.c=.o)

CFLAGS = -Wall -Wextra -Werror

FLAGS = -g -Iminilibx-linux -Lminilibx-linux -lmlx -lXext -lX11 -lm -lz

all: $(ARCHIVE_NAME)
	$(CC) $(CFLAGS) $(MY_OBJECTS) $(FLAGS) -o $(PROGRAM_NAME)
	$(MAKE) clean
	
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
