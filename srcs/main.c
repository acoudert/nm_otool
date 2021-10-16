#include "ft_nm.h"

char	g_arch;
t_args  g_args;
int		g_file_no;

static char		is_elf(unsigned char *e_ident) {
	if (e_ident[EI_MAG0] == ELFMAG0 && e_ident[EI_MAG1] == ELFMAG1 \
			&& e_ident[EI_MAG2] == ELFMAG2 && e_ident[EI_MAG3] == ELFMAG3)
		return 1;
	return 0;
}

static inline int	ft_analyze(char *path, void *p, size_t file_size) {
	unsigned char	*e_ident;

	if (file_size < EI_NIDENT)
		return error(path, FORMAT_STR, 0);
	e_ident = (unsigned char*)p;
	if (is_elf(e_ident)) {
		if (file_size >= 52 && e_ident[EI_CLASS] == ELFCLASS32)
			return analyze_32(path, p, file_size);
		else if (file_size >= 64 && e_ident[EI_CLASS] == ELFCLASS64)
			return analyze_64(path, p, file_size);
		return error(path, FORMAT_STR, 0);
	}
	return error(path, FORMAT_STR, 0);
}

static int		ft_nm(char *path) {
	int				fd;
	struct stat		path_stat;
	void			*p;

	if ((fd = open(path, O_RDONLY)) > 0) {
		if (fstat(fd, &path_stat) != 0) {
			close(fd);
			return error(path, NULL, 0);
		}
		if (S_ISDIR(path_stat.st_mode)) {
			close(fd);
			return error(path, DIR_STR, 1);
		}
		if (path_stat.st_size == 0) {
			close(fd);
			return 0;
		}
		p = mmap(0, path_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
		close(fd);
		if (p == MAP_FAILED)
			return error(path, NULL, 0);
		if (ft_analyze(path, p, path_stat.st_size)) {
			munmap(p, path_stat.st_size);
			return 1;
		}
		munmap(p, path_stat.st_size);
		return 0;
	}
	return error(path, NULL, 0);
}

int				main(int ac, char **av) {
	int		final_value = 0;
	int		ret_value;

	g_file_no = set_up_args(ac, av);
	if (g_file_no == -1)
		return 1;
	else if (g_file_no == -2)
		return 0;
	else if (g_file_no == 0)
		return ft_nm("a.out");
	for (int i=1; i < ac; i++) {
		if (av[i][0]) {
			g_args.file_name = av[i];
			ret_value = ft_nm(av[i]);
			final_value = (ret_value) ? ret_value : final_value;
		}
	}
	return final_value;
}
