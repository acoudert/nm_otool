#include "ft_nm.h"

void	print_help() {
	printf("Usage: ./ft_nm [OPTION]... FILE\n");
	printf("Options:\n");
	printf("\t-h: This help\n");
	printf("\t-n: Numeric sort\n");
	printf("\t-p: No sort\n");
	printf("\t-r: Reverse sort\n");
	printf("\t-S: Print size\n");
	printf("\t-o: Preceed each symbol by the name of the input file\n");
}

char	update_args(char *str) {
	for (unsigned int i=1; i < ft_strlen(str); i++) {
		if (str[i] == 'n') {
			g_args.sort_type = SORT_TYPE_NUMERIC;
			continue ;
		} else if (str[i] == 'p') {
			g_args.sort_type = SORT_TYPE_NONE;
			continue ;
		} else if (str[i] == 'r') {
			g_args.sort_order = SORT_ORDER_REVERSE;
			continue ;
		} else if (str[i] == 'h') {
			print_help();
			return -2;
		} else if (str[i] == 'S') {
			g_args.print_size = 1;
			continue ;
		} else if (str[i] == 'o') {
			g_args.print_name = 1;
			continue ;
		}
		return 0;
	}
	return 1;
}

int		set_up_args(int ac, char **av) {
	int		ret_update;
	int		ret;

	g_args.sort_order = SORT_ORDER_DEFAULT;
	g_args.sort_type = SORT_TYPE_DEFAULT;
	g_args.print_size = 0;
	g_args.print_name = 0;
	g_args.file_name = NULL;
	ret = 0;
	if (ac == 1)
		return 0;
	for (int i=1; i < ac; i++) {
		if (av[i][0] == '-' && ft_strlen(av[i]) != 1) {
			ret_update = update_args(av[i]);
			if (ret_update == 1)
				av[i][0] = 0;
			else if (ret_update == -2) {
				return -2;
			}
			else {
				print_help();
				return -1;
			}
		} else
			ret++;
	}
	return ret;
}
