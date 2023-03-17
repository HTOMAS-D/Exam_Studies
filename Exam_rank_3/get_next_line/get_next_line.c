#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

char *get_next_line(int fd)
{
    int     i = 0;
    int     rd = 0;
    char    character;
    char     *buffer = malloc(10000);

    if (BUFFER_SIZE <= 0)
		return (free(buffer), NULL);
    while ((rd = read(fd, &character, BUFFER_SIZE - BUFFER_SIZE + 1)) > 0)
    {
        buffer[i++] = character;
        if (character == '\n')
            break;
    }
    if ((!buffer[i - 1] && !rd) || rd == -1)
    {
        free(buffer);
        return (NULL);
    }
    buffer[i] =  '\0';
    return(buffer);
}

int main(){
	int fd = open("cenas", O_RDONLY);
	char *line;
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	printf("ola");
	printf("ola");
	printf("ola");
	printf("ola");
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	printf("ola");
	printf("ola");
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
}