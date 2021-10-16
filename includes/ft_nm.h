#ifndef FT_NM_H
# define FT_NM_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <sys/errno.h>
# include <string.h>
# include <elf.h>
# include <ar.h>

# include "libft.h"

/*
 * ERRORS
*/

# define ENOENT_STR		"No such file"
# define EACCES_STR		"Permission denied"
# define DIR_STR		"is a directory"
# define FORMAT_STR		"file format not recognized"
# define NO_SYM			"no symbols"
# define FATAL_STR		"fatal error"

/*
 * ARGS
*/

# define SORT_ORDER_DEFAULT	0
# define SORT_ORDER_REVERSE	1
# define SORT_TYPE_DEFAULT	0
# define SORT_TYPE_NUMERIC	1
# define SORT_TYPE_NONE		2

typedef struct	s_args {
	char	sort_order;
	char	sort_type;
	char	print_size;
	char	print_name;
	char	*file_name;
}				t_args;

extern	t_args	g_args;
extern int		g_file_no;

/*
 * DATA
*/

# define SHDR_NAME(data, i)		((char*)data->shstr + data->shdr[i].sh_name)
# define SYM_NAME(data, i)		((char*)data->str + data->symtab[i].st_name)

extern char		g_arch;

typedef struct	s_data64 {
	void			*start;
	Elf64_Ehdr		*ehdr;
	Elf64_Shdr		*shdr;
	Elf64_Shdr		*shdr_str;
	Elf64_Shdr		*shdr_sym;
	Elf64_Sym		*symtab;
	char			*shstr;
	char			*str;
	size_t			len_symtab;
	size_t			file_size;
}				t_data64;

typedef struct	s_data32 {
	void			*start;
	Elf32_Ehdr		*ehdr;
	Elf32_Shdr		*shdr;
	Elf32_Shdr		*shdr_str;
	Elf32_Shdr		*shdr_sym;
	Elf32_Sym		*symtab;
	char			*shstr;
	char			*str;
	size_t			len_symtab;
	size_t			file_size;
}				t_data32;

typedef struct	s_sym {
	char			*sym_name;
	unsigned char	sym_type;
	unsigned char	sym_bind;
	unsigned char	sym_vis;
	unsigned long	sym_value;
	unsigned long	sym_size;
	unsigned short	shdr_index;
	char			*shdr_name;
	unsigned int	shdr_link;
	unsigned int	shdr_type;
	unsigned long	shdr_flags;
}				t_sym;

/*
 * FUNCTIONS
*/

int		set_up_args(int ac, char **av);

int		error(char *path, char *err, char warning);
void	quick_sort_asc(t_sym *syms, int start, int end);
void    display_symbols(t_sym *syms, size_t size);

int		analyze_32(char *file, void *p, size_t file_size);
char	set_up_data32(t_data32 **data, char *file, void *p);

int		analyze_64(char *file, void *p, size_t file_size);
char	set_up_data64(t_data64 **data, char *file, void *p);

#endif
