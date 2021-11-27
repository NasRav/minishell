CC =		gcc
RM =		/bin/rm -f
INCLUDES =	.
CFLAGS =	-Wall -Wextra -Werror

NAME =	libft.a

SRCS = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
	ft_memchr.c ft_memcmp.c \
	ft_strlen.c ft_strcpy.c ft_strlcpy.c ft_strlcat.c ft_strchr.c \
	ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_substr.c ft_strjoin.c \
	ft_strtrim.c ft_strdup.c ft_strmapi.c ft_strcmp.c ft_isnumber.c\
	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_toupper.c ft_tolower.c ft_calloc.c ft_split.c ft_itoa.c ft_atoi.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_putchar.c ft_putstr.c ft_putendl.c \
	ft_putnbr.c ft_realloc.c get_next_line.c \
	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstdelone.c \
	ft_lstadd_back.c ft_lstclear.c ft_lstiter.c \
	ft_lstnew2.c ft_lstadd_front2.c ft_lstclear2.c ft_lstlast2.c ft_lstfirst2.c\
	ft_lstadd_back2.c ft_lstdelone2.c ft_lstmap2.c \
	ft_printf/format_len.c ft_printf/format_output.c \
	ft_printf/format_putnbr.c ft_printf/ft_printf.c \
	ft_printf/ft_printf_utils.c ft_printf/printf_parser.c \
	ft_printf/type_d_i.c ft_printf/type_handler.c ft_printf/type_p.c \
	ft_printf/type_u.c ft_printf/type_x.c


OBJ_FILES =	$(SRCS:.c=.o)

.c.o:
		$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES)

$(NAME):	$(OBJ_FILES) libft.h
		ar rc $(NAME) $(OBJ_FILES)
		ranlib $(NAME)

so:
		$(CC) -shared $(OBJ_FILES) -o libft.so

all:	$(NAME)

clean:
		$(RM) $(OBJ_FILES) libft.so

fclean:	clean
		$(RM) $(NAME)

re:		fclean \
		all

.PHONY: all clean fclean re
