#include "./read_file.h"

#include "./t_string/t_string.h"

#include <unistd.h>
#include <fcntl.h>

static t_error read_from_fd(int fd, t_string **output);

t_error read_file(const char *filename, char **output)
{
	int fd;
	t_error err;
	t_string *file;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (E_OPEN);
	file = string_new_with_capacity(READ_FILE_BUFFER_SIZE);
	if (!file)
	{
		close(fd);
		return (E_OOM);
	}
	err = read_from_fd(fd, &file);
	if (err != NO_ERROR)
	{
		string_destroy(file);
		close(fd);
		return (err);
	}
	err = string_make_c_string(file, output);
	string_destroy(file);
	close(fd);
	return (err);
}

static t_error read_from_fd(int fd, t_string **output)
{
	ssize_t	bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		if (string_reserve(output, READ_FILE_BUFFER_SIZE))
			return (E_OOM);
		bytes_read = read(fd, &(*output)->data[(*output)->len], READ_FILE_BUFFER_SIZE);
		if (bytes_read > 0)
			(*output)->len += bytes_read;
	}
	if (bytes_read < 0)
		return (E_READ);
	return (NO_ERROR);
}
