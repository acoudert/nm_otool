#include "ft_nm.h"

static void		swap_symbol(t_sym *a, t_sym *b)
{
	t_sym	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int		partition_desc(t_sym *sym, int start, int end)
{
	char	*pivot_name;
	int		pivot_value;
	char	*name;
	int		i;
	int		j;
	int		comp;

	pivot_name = sym[end].sym_name;
	pivot_value = sym[end].sym_value;
	i = start - 1;
	j = start;
	while (j <= end - 1)
	{
		name = sym[j].sym_name;
		if (g_args.sort_type == SORT_TYPE_DEFAULT) {
			comp = strcmp(name, pivot_name);
			if (comp <= 0)
			{
				if (comp < 0 || sym[end].sym_value < sym[j].sym_value) {
					i++;
					swap_symbol(sym + i, sym + j);
				}
			}
		} else {
			comp = sym[j].sym_value - pivot_value;
			if (comp <= 0)
			{
				if (comp < 0 || ft_strcmp(name, pivot_name) > 0) {
					i++;
					swap_symbol(sym + i, sym + j);
				}
			}
		}
		j++;
	}
	swap_symbol(sym + i + 1, sym + end);
	return (i + 1);
}

static int		partition_asc(t_sym *sym, int start, int end)
{
	char	*pivot_name;
	int		pivot_value;
	char	*name;
	int		i;
	int		j;
	int		comp;

	pivot_name = sym[end].sym_name;
	pivot_value = sym[end].sym_value;
	i = start - 1;
	j = start;
	while (j <= end - 1)
	{
		name = sym[j].sym_name;
		if (g_args.sort_type == SORT_TYPE_DEFAULT) {
			comp = strcmp(name, pivot_name);
			if (comp <= 0)
			{
				if (comp < 0 || sym[end].sym_value > sym[j].sym_value) {
					i++;
					swap_symbol(sym + i, sym + j);
				}
			}
		} else {
			comp = sym[j].sym_value - pivot_value;
			if (comp <= 0)
			{
				if (comp < 0 || ft_strcmp(name, pivot_name) < 0) {
					i++;
					swap_symbol(sym + i, sym + j);
				}
			}
		}
		j++;
	}
	swap_symbol(sym + i + 1, sym + end);
	return (i + 1);
}

void			quick_sort_desc(t_sym *sym, int start, int end)
{
	int		pi;

	if (start < end)
	{
		pi = partition_desc(sym, start, end);
		quick_sort_desc(sym, start, pi - 1);
		quick_sort_desc(sym, pi + 1, end);
	}
}

void			quick_sort_asc(t_sym *sym, int start, int end)
{
	int		pi;

	if (start < end)
	{
		pi = partition_asc(sym, start, end);
		quick_sort_asc(sym, start, pi - 1);
		quick_sort_asc(sym, pi + 1, end);
	}
}
