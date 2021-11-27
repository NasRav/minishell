#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
char				*ft_strcpy(char *dst, const char *src);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *big, const char *little, size_t l);
int					ft_strncmp(const char *s1, const char *s2, size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_atoi(const char *nptr);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_isnumber(char *num);
int					ft_toupper(int c);
int					ft_tolower(int c);

void				*ft_calloc(size_t nmemb, size_t size);
void				*ft_realloc(void *ptr, int size, int newsize);
char				*ft_strdup(const char *s);

char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putchar(char c);
void				ft_putstr(char *s);
void				ft_putendl(char *s);
void				ft_putnbr(int n);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_list2
{
	char			*content;
	struct s_list2	*prev;
	struct s_list2	*next;
}					t_list2;

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list2				*ft_lstnew2(void *content);
void				ft_lstadd_front2(t_list2 **lst, t_list2 *new);
void				ft_lstclear2(t_list2 **lst, void (*del)(void *));
t_list2				*ft_lstlast2(t_list2 *lst);
t_list2				*ft_lstfirst2(t_list2 *lst);
void				ft_lstadd_back2(t_list2 **lst, t_list2 *new);
void				ft_lstdelone2(t_list2 **lst, void (*del)(void *));
t_list2				*ft_lstmap2(t_list2 *lst, char *(*f)(const char *), \
					void (*del)(void *));

int					get_next_line(int fd, char **line);

typedef struct s_flags
{
	char			null;
	int				right;
	int				left;
	int				dot;
	char			x;
}					t_flags;

int					ft_printf(const char *format, ...);

size_t				format_putchar(char c, size_t bytes);
size_t				format_putstr(char *s, size_t bytes);
size_t				format_putnbr(int nbr, size_t bytes);

size_t				ft_putnbr_p(size_t nbr, size_t bytes);
size_t				ft_putnbr_u(unsigned int nbr, size_t bytes);
size_t				ft_putnbr_x(unsigned int nbr, size_t bytes);
size_t				ft_putnbr_xx(unsigned int nbr, size_t bytes);

size_t				type_asterisk(va_list ap, const char *format, size_t i, \
					int *star);
size_t				check_flags(const char *format, va_list ap, size_t i, \
					size_t *bytes);
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
int					ft_isflag(int c);

size_t				ft_len_int(int nbr);
size_t				ft_len_p(size_t nbr);
size_t				ft_len_u(unsigned int nbr);
size_t				ft_len_o(unsigned int nbr);
size_t				ft_len_x(unsigned int nbr);

size_t				type_c(va_list ap, size_t bytes, t_flags flag);
size_t				type_d_i(va_list ap, size_t bytes, t_flags flag);
size_t				type_p(va_list ap, size_t bytes, t_flags flag);
size_t				type_percent(size_t bytes, t_flags flag);
size_t				type_s(va_list ap, size_t bytes, t_flags flag);
size_t				type_u(va_list ap, size_t bytes, t_flags flag);
size_t				type_x(va_list ap, size_t bytes, t_flags flag);

#endif
