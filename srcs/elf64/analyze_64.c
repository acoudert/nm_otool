#include "ft_nm.h"

static void	set_up_section_info(t_sym *syms, t_data64 *data, size_t i) {
	int		shndx;

	shndx = data->symtab[i].st_shndx;
	syms[i].shdr_index = shndx;
	if ((shndx >= SHN_LORESERVE && shndx <= SHN_HIRESERVE) || \
			shndx == SHN_UNDEF) {
		syms[i].shdr_name = "";
		syms[i].shdr_link = 0;
		syms[i].shdr_type = 0;
		syms[i].shdr_flags = 0;
	} else {
		syms[i].shdr_name = SHDR_NAME(data, shndx);
		syms[i].shdr_link = data->shdr[shndx].sh_link;
		syms[i].shdr_type = data->shdr[shndx].sh_type;
		syms[i].shdr_flags = data->shdr[shndx].sh_flags;
	}
}

static t_sym	*get_symbols(t_data64 *data) {
	t_sym	*syms = NULL;

	if (!(syms = (t_sym*)malloc(sizeof(t_sym) * data->len_symtab)))
		return NULL;
	for (size_t i=0; i < data->len_symtab; i++) {
		syms[i].sym_name = SYM_NAME(data, i);
		syms[i].sym_type = ELF64_ST_TYPE(data->symtab[i].st_info);
		syms[i].sym_bind = ELF64_ST_BIND(data->symtab[i].st_info);
		syms[i].sym_vis = ELF64_ST_VISIBILITY(data->symtab[i].st_other);
		syms[i].sym_value = data->symtab[i].st_value;
		syms[i].sym_size = data->symtab[i].st_size;
		set_up_section_info(syms, data, i);
	}
	return syms;
}

int     analyze_64(char *file, void *p, size_t file_size) {
	Elf64_Ehdr	*ehdr;
	t_data64	*data;
	t_sym		*syms;

	ehdr = (Elf64_Ehdr*)p;
	if (file_size < ehdr->e_shoff + (ehdr->e_shentsize * ehdr->e_shnum))
		return error(file, FORMAT_STR, 0);
	g_arch = ELFCLASS64;
	if (set_up_data64(&data, file, p))
		return 1;
	if (!data->shdr_str) {
		error(file, NO_SYM, 0);
		free(data);
		return 0;
	}
	syms = get_symbols(data);
	if (!syms) {
		error(file, FATAL_STR, 0);
		free(data->symtab);
		free(data);
		return 1;
	}
	display_symbols(syms, data->len_symtab);
	free(syms);
	free(data->symtab);
	free(data);
	return 0;
}
