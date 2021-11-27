NAME =		minishell

CC =		gcc
RM =		/bin/rm -f
CFLAGS =	-Wall -Wextra -Werror
INCLUDES =	includes

SRCS =		srcs/exec_builtins.c\
			srcs/executor.c\
			srcs/export_utils.c\
			srcs/find_cmd.c\
			srcs/ft_cd.c\
			srcs/ft_exit.c\
			srcs/ft_export.c\
			srcs/ft_unset.c\
			srcs/get_from_env.c\
			srcs/handle_line.c\
			srcs/history.c\
			srcs/key_press.c\
			srcs/lexer.c\
			srcs/main.c\
			srcs/minish_utils.c\
			srcs/parser.c\
			srcs/pipe_utils.c\
			srcs/preparser.c\
			srcs/queue.c\
			srcs/read_cmds.c\
			srcs/redirects.c\
			srcs/split_vars.c\
			srcs/utils.c


OBJS =		$(SRCS:.c=.o)


.c.o :		$(INCLUDES)/minishell.h libft/libft.h
			$(CC) $(CFLAGS) -Ilibft -I $(INCLUDES) -c $< -o $(<:.c=.o)


$(NAME) :	$(OBJS)	$(INCLUDES)/minishell.h libft/libft.h
			make -C libft
			cp libft/libft.a .
			$(CC) -o $(NAME) $(OBJS) libft.a -I libft -I $(INCLUDES) -l termcap


all :		$(NAME)

clean :
			$(RM) $(OBJS)
			$(RM) .minish_history .minish_heredoc
			make clean -C libft

fclean :	clean
			make fclean -C libft
			$(RM) libft.a
			$(RM) .minish_history
			$(RM) $(NAME)

re :		fclean \
			all

.PHONY :	all clean fclean re
