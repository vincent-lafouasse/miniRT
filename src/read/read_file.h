#ifndef READ_FILE_H
#define READ_FILE_H

#include "error/t_error.h"
#include "./t_string/t_string.h"

#define READ_FILE_BUFFER_SIZE 4096

t_error read_file(const char *filename, char **output);

#endif // READ_FILE_H
