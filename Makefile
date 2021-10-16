NAME         = ft_nm
CC           = gcc
CINCLUDES    = -I includes -I libft
CFLAGS      = -Wall -Wextra -Werror $(CINCLUDES)
RM           = rm -f
DIR          = srcs
SRCS         = $(DIR)/main.c \
			   $(DIR)/set_up_args.c \
			   $(DIR)/error.c \
			   $(DIR)/quick_sort.c \
			   $(DIR)/display_symbols.c \
			   $(DIR)/elf32/analyze_32.c \
			   $(DIR)/elf32/set_up_data32.c \
			   $(DIR)/elf64/analyze_64.c \
			   $(DIR)/elf64/set_up_data64.c
OBJS         = $(SRCS:.c=.o)
DIR_TEST     = tests
SRCS_TEST    = $(DIR_TEST)/test_facile.c \
			   $(DIR_TEST)/test_moins_facile.c
OBJS_TEST32  = $(SRCS_TEST:.c=32.o)
OBJS_TEST64  = $(SRCS_TEST:.c=64.o)
OUT_TEST32  = $(SRCS_TEST:.c=32)
OUT_TEST64  = $(SRCS_TEST:.c=64)

all          : $(NAME)

$(NAME)      : $(OBJS)
	@$(MAKE) -C libft --no-print-director
	$(CC) $^ -o $@ -L libft -l ft

$(OBJS)      : %.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

re           : fclean all

clean        :
	@$(MAKE) clean -C libft --no-print-directory
	$(RM) $(OBJS_TEST32) $(OUT_TEST32)
	$(RM) $(OBJS_TEST64) $(OUT_TEST64)
	$(RM) $(OBJS)

fclean       : clean
	@$(MAKE) fclean -C libft --no-print-directory
	$(RM) $(NAME)

test         : all cc_test
	bash test.sh

cc_test      : $(OUT_TEST32) $(OUT_TEST64)

$(OUT_TEST32) : %32 : %.c
	$(CC) -m32 -o $@.o -c $<
	$(CC) -m32 -o $@ $@.o

$(OUT_TEST64) : %64 : %.c
	$(CC) -o $@.o -c $<
	$(CC) -o $@ $@.o

.PHONY     : all bonus re clean fclean test cc_test
