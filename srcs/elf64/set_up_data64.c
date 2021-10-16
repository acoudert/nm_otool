#include "ft_nm.h"

static inline void get_direct_values(t_data64 *data, void *p) {
	data->start = p;
	data->ehdr = (Elf64_Ehdr*)p;
	data->shdr = (Elf64_Shdr*)(data->start + data->ehdr->e_shoff);
	data->shstr = (char*)(data->start + data->shdr[data->ehdr->e_shstrndx].sh_offset);
}

static inline void	get_shdr_tabs(t_data64 *data) {
	char	*name;

	data->shdr_str = NULL;
	data->shdr_sym = NULL;
	data->symtab = NULL;
	for (int i=0; i < data->ehdr->e_shnum; i++) {
		name = SHDR_NAME(data, i);
		if (strcmp(name, ".strtab") == 0)
			data->shdr_str = data->shdr + i;
		else if (strcmp(name, ".symtab") == 0)
			data->shdr_sym = data->shdr + i;
	}
}

char	set_up_data64(t_data64 **data, char *file, void *p) {
	void        *symtab;

	if (!(*data = (t_data64*)malloc(sizeof(t_data64))))
		return error(file, FATAL_STR, 0);
	get_direct_values(*data, p);
	get_shdr_tabs(*data);
	if (!(*data)->shdr_str)
		return 0;
	(*data)->str = (char*)((*data)->start + (*data)->shdr_str->sh_offset);
	symtab = (*data)->start + (*data)->shdr_sym->sh_offset;
	if (!((*data)->symtab = (Elf64_Sym*)malloc((*data)->shdr_sym->sh_size))) {
		free(*data);
		return error(file, FATAL_STR, 0);
	}
	ft_memcpy((*data)->symtab, symtab, (*data)->shdr_sym->sh_size);
	(*data)->len_symtab = (*data)->shdr_sym->sh_size / sizeof(Elf64_Sym);
	return 0;
}
