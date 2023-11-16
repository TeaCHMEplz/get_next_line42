/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: stein  <sduray@42.nl>                        +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/09 09:35:22 by duray         #+#    #+#                 */
/*   Updated: 2023/11/16 17:30:58 by sduray        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_buffer(char **str)
{
	if (*str != NULL)
		free(*str);
	*str = NULL;
}

static char	*read_to_newline(int fd, char *buf, char *backup)
{
	int		read_line;
	char	*char_temp;

	read_line = 1;
	while (read_line != '\0')
	{
		read_line = read(fd, buf, BUFFER_SIZE);
		if (read_line == -1)
			return (NULL);
		else if (read_line == 0)
			break ;
		buf[read_line] = '\0';
		if (!backup)
			backup = ft_strdup("");
		if (backup = NULL)
			return (free(backup), (NULL));
		char_temp = backup;
		backup = ft_strjoin(char_temp, buf);
		if (backup == NULL)
			return (free(backup), (NULL));
		free_buffer(&char_temp);
		if (ft_strchr (buf, '\n'))
			break ;
	}
	return (backup);
}

static char	*extract(char *line)
{
	size_t	count;
	char	*backup;

	count = 0;
	while (line[count] != '\n' && line[count] != '\0')
		count++;
	if (line[count] == '\0')
		return (0);
	backup = ft_substr(line, count + 1, ft_strlen(line) - count);
	if (backup == NULL)
		return (NULL);
	if (*backup == '\0')
	{
		free(backup);
		backup = NULL;
	}
	line[count + 1] = '\0';
	return (backup);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*backup;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (free(buf), (NULL));
	line = read_to_newline(fd, buf, backup);
	free(buf);
	buf = NULL;
	if (!line)
		return (NULL);
	backup = extract(line);
	return (line);
}

int main()
{
	int fd = open("test", O_RDONLY);
	while(printf("%s", get_next_line(fd)) != 6)
		;
}