#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <string.h>
# include <errno.h>
# include <term.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <curses.h>

typedef struct s_queue
{
	char			*line;
	int				option;
	struct s_queue	*next;
}					t_queue;

typedef struct s_cmd
{
	t_queue			*cmd;
	t_queue			*rd;
	int				err;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_term
{
	struct termios	icanon_term;
	t_list2			*history;
	t_list2			*cmd_line;
	unsigned int	curs;
}					t_term;

void		sig_handler(int signum);
t_term		*term_set(t_term *term, int term_n);
int			get_cmd(t_term *term);

char		ctrl_c(t_term *term);
char		backspace(t_term *term);
int			arrow_key_press(t_term *term, char n);

t_list2		*get_history(void);
void		save_history(t_list2 **list);
void		put_history(t_term *term, char n);

void		lexer(char *line, t_queue **lex);
void		handle_cmdline(t_list2 *history, char ***envp);
int			parse_pipe(char **tok, t_queue **lex);
int			parse_quot(char quot, char *line, char **tok, t_queue **lex);
int			parse_rd(char *line, char **tok, t_queue **lex);

void		cmd_init(t_cmd **par);
void		parser(t_queue **lex, t_cmd **par);

void		get_from_env(t_cmd **par, char **envp);

char		*char_to_str(char c);
void		split_whitespaces(char **result, t_queue **var);

void		executor(t_list2 *history, char ***envp, t_cmd **par);

void		set_cmd_queue(char ***argc, t_queue *cmd);
void		execute(char **div_path, char ***envp, t_queue *cmd);

int			rd_left(t_queue *red);
int			rd_right(t_queue *red);
int			rd_append(t_queue *red);
int			rd_heredoc(int std_in, t_queue *red);

void		push_queue(int op, char *line, t_queue **queue);
char		*pop_queue(t_queue **queue);

void		join_free(int mode, char **src, char *dst);
int			check_closed(int x, char *line);
int			my_putchar(int c);
void		free_array(char **array);
char		*ft_getenv(char *key, char **envp);
char		*ft_getcwd(void);
char		*get_errorvar(int exit_status, int ret);

int			exec_builtin(t_list2 *history, char ***argv, char ***envp);
int			ft_exit(t_list2 *history, char **argv);

int			ft_cd(char **argv, char ***envp);

int			ft_export(char ***envp, char **argv);
void		split_env(char *string, char **variable, char **value);

int			compare_env_var(char *env, char *new_env);
void		print_export(char **envp);
int			is_valid_val(char *line);

void		ft_unset(char ***envp, char **argv);

int			ft_exit(t_list2 *history, char **argv);

void		ft_pipe(t_cmd *tmp, int fd[2], pid_t pid);
void		reset_fds(int mode);
pid_t		fork_pids(pid_t **pids);
void		wait_pids(pid_t *pids);

#endif
