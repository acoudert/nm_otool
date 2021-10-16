#include "ft_nm.h"

static char		get_symbol_case(unsigned char sym_bind, char c) {
	if (sym_bind == STB_GLOBAL)
		return c;
	return ft_tolower(c);
}

static char		value_to_print(t_sym sym, char c) {
	if (sym.sym_value)
		return 1;
	else if (ft_tolower(c) == 't')
		return 1;
	else if (ft_tolower(c) == 'a')
		return 1;
	else if (ft_tolower(c) == 'n')
		return 1;
	else if (ft_tolower(c) == 'b')
		return 1;
	else if (ft_tolower(c) == 'r')
		return 1;
	else if (ft_tolower(c) == 'd')
		return 1;
	else if (c == 'W')
		return 1;
	return 0;
}

static void	print_line(t_sym sym, char c) {
	if (g_args.print_name)
		printf("%s:", g_args.file_name);
	if (g_arch == ELFCLASS32) {
		if (value_to_print(sym, c))
			if (g_args.print_size && sym.sym_size)
				printf("%08lx %08lx %c %s\n", sym.sym_value, sym.sym_size, c, sym.sym_name);
			else
				printf("%08lx %c %s\n", sym.sym_value, c, sym.sym_name);
		else
			printf("%8s %c %s\n", "", c, sym.sym_name);
	} else {
		if (value_to_print(sym, c))
			if (g_args.print_size && sym.sym_size)
				printf("%016lx %016lx %c %s\n", sym.sym_value, sym.sym_size, c, sym.sym_name);
			else
				printf("%016lx %c %s\n", sym.sym_value, c, sym.sym_name);
		else
			printf("%16s %c %s\n", "", c, sym.sym_name);
	}
}

static char	display_section_spec_meaning(t_sym sym) {
	int	shndx;

	shndx = sym.shdr_index;
	if (shndx >= SHN_LORESERVE && shndx <= SHN_HIRESERVE) {
		if (shndx == SHN_ABS) {
			print_line(sym, get_symbol_case(sym.sym_bind, 'A'));
			return 1;
		} else if (shndx == SHN_COMMON) {
			print_line(sym, 'C');
			return 1;
		}
	} else if (sym.sym_type == STT_LOOS \
			&& sym.shdr_flags & SHF_ALLOC \
			&& sym.shdr_flags & SHF_EXECINSTR) {
		print_line(sym, 'i');
		return 1;
	} else if (sym.sym_bind == STB_WEAK) {
		if (sym.sym_type == STT_OBJECT) {
			if (sym.sym_value)
				print_line(sym, 'V');
			else
				print_line(sym, 'v');
		} else {
			if (sym.sym_value || sym.shdr_index)
				print_line(sym, 'W');
			else
				print_line(sym, 'w');
		}
		return 1;
	} else if (sym.sym_type == STT_OBJECT && sym.sym_bind == STB_GNU_UNIQUE) {
		print_line(sym, 'u');
		return 1;
	}
	return 0;
}

static char	display_section_name(t_sym sym) {
	if (strncmp(sym.shdr_name, ".bss", 4) == 0) {
		print_line(sym, get_symbol_case(sym.sym_bind, 'B'));
		return 1;
	} else if (strncmp(sym.shdr_name, ".text", 5) == 0) {
		print_line(sym, get_symbol_case(sym.sym_bind, 'T'));
		return 1;
	} else if (strncmp(sym.shdr_name, ".data", 5) == 0) {
		print_line(sym, get_symbol_case(sym.sym_bind, 'D'));
		return 1;
	} else if (strncmp(sym.shdr_name, ".rodata", 7) == 0) {
		print_line(sym, get_symbol_case(sym.sym_bind, 'R'));
		return 1;
	}
	return 0;
}

static char	display_section_flag_type(t_sym sym) {
	if (sym.shdr_type == SHT_NOBITS \
			&& sym.shdr_flags & SHF_ALLOC \
			&& !(sym.shdr_flags & SHF_EXECINSTR)) {
		print_line(sym, get_symbol_case(sym.sym_bind, 'B'));
		return 1;
	} else if (!(sym.shdr_flags & SHF_WRITE) \
			&& sym.shdr_flags & SHF_ALLOC \
			&& !(sym.shdr_flags & SHF_EXECINSTR)) {
		print_line(sym, get_symbol_case(sym.sym_bind, 'R'));
		return 1; 
	} else if (sym.shdr_flags & SHF_WRITE \
			&& sym.shdr_flags & SHF_ALLOC) {
		print_line(sym, get_symbol_case(sym.sym_bind, 'D'));
		return 1;
	} else if (sym.shdr_flags & SHF_ALLOC \
			&& sym.shdr_flags & SHF_EXECINSTR) {
		print_line(sym, get_symbol_case(sym.sym_bind, 'T'));
		return 1;
	} else if (sym.shdr_type == SHT_PROGBITS \
			&& !sym.shdr_flags) {
		print_line(sym, get_symbol_case(sym.sym_bind, 'N'));
		return 1; 
	}
	return 0;
}

static void	display_symbol_line(t_sym sym) {
	if (!sym.sym_name[0] || sym.sym_type == STT_FILE)
		return ;
	else if (display_section_spec_meaning(sym))
		return ;
	else if (display_section_name(sym))
		return ;
	else if (display_section_flag_type(sym))
		return ;
	print_line(sym, 'U');
}

void	display_symbols(t_sym *syms, size_t size) {
	if (g_file_no > 1)
		printf("\n%s:\n", g_args.file_name);
	if (g_args.sort_type != SORT_TYPE_NONE)
		quick_sort_asc(syms, 0, size - 1);
	if (g_args.sort_order == SORT_ORDER_DEFAULT)
		for (size_t i=0; i < size; i++)
			display_symbol_line(syms[i]);
	else
		for (size_t i=size; i > 0; i--)
			display_symbol_line(syms[i-1]);
}
