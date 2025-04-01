#include "./t_error.h"

#include <stdio.h>

void log_error(t_error err)
{
	printf("Error\n");
	printf("%s\n", error_repr(err));
}
