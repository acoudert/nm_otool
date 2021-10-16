#include "ft_nm.h"

static inline void	error_middle(char *path, char warning) {
	if (warning)
		ft_putstr_fd("Warning: ", STDERR_FILENO);
	else if (errno) {
		ft_putstr_fd("'", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd("': ", STDERR_FILENO);
	} else {
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
}

static inline void error_errno() {
	if (errno == ENOENT)
		ft_putstr_fd(ENOENT_STR, STDERR_FILENO);
	else if (errno == EACCES)
		ft_putstr_fd(EACCES_STR, STDERR_FILENO);
}

static inline void error_other(char *path, char *err, char warning) {
	if (warning) {
		ft_putstr_fd("'", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd("' ", STDERR_FILENO);
	}
	ft_putstr_fd(err, STDERR_FILENO);
}

int		error(char *path, char *err, char warning) {
	ft_putstr_fd("nm: ", STDERR_FILENO);
	error_middle(path, warning);
	(err || warning) ? error_other(path, err, warning) : error_errno();
	ft_putstr_fd("\n", STDERR_FILENO);
	return 1;
}

