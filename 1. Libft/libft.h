#ifndef LIBFT_H
#define LIBFT_H

#include <stdlib.h>
#include <stddef.h>  // for size_t
#include <unistd.h>

// Memory functions
void    *ft_memset(void *s, int c, size_t n);
void    ft_bzero(void *s, size_t n);
void    *ft_memcpy(void *dst, const void *src, size_t n);
void    *ft_memmove(void *dst, const void *src, size_t len);
void    *ft_memchr(const void *s, int c, size_t n);
int     ft_memcmp(const void *s1, const void *s2, size_t n);

// String functions
size_t  ft_strlen(const char *s);
size_t ft_strlcpy(char *dest, const char *src, size_t size);
char    *ft_strdup(const char *s1);
char    *ft_strchr(const char *s, int c);
char    *ft_strrchr(const char *s, int c);
char    *ft_strnstr(const char *haystack, const char *needle, size_t len);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
char    *ft_strjoin(const char *s1, const char *s2);
char    *ft_substr(const char *s, unsigned int start, size_t len);
char    *ft_strtrim(char const *s1, char const *set);
char    *ft_strmapi(const char *s, char (*f)(unsigned int, char));
void    ft_striteri(char *s, void (*f)(unsigned int, char*));

// Conversion functions
int     ft_atoi(const char *str);
char    *ft_itoa(int n);

// Character functions
int     ft_isalpha(int c);
int     ft_isdigit(int c);
int     ft_isalnum(int c);
int     ft_isascii(int c);
int     ft_isprint(int c);
int     ft_tolower(int c);
int     ft_toupper(int c);

// List functions (if you have linked list implementations)
typedef struct s_list {
    void            *content;
    struct s_list   *next;
} t_list;

t_list  *ft_lstnew(void *content);
void    ft_lstadd_front(t_list **alst, t_list *new);
void    ft_lstadd_back(t_list **alst, t_list *new);
void    ft_lstdelone(t_list *lst, void (*del)(void *));
void    ft_lstclear(t_list **lst, void (*del)(void *));
void    ft_lstiter(t_list *lst, void (*f)(void *));
t_list  *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// Other functions
void    ft_putchar_fd(char c, int fd);
void    ft_putstr_fd(char *s, int fd);
void    ft_putendl_fd(char *s, int fd);
void    ft_putnbr_fd(int n, int fd);
// void    ft_split(const char *s, char c);  Modify according to your implementation
char **ft_split(const char *str, char delim);
#endif
