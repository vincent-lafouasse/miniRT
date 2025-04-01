#include "./t_error.h"

#include <stdlib.h>

__attribute__((noreturn))
void	die(t_error err, int exit_code)
{
	log_error(err);
	exit(exit_code);
}
