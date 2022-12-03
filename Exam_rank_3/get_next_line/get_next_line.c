#include "get_next_line.h"

char *get_next_line(int fd){
	int i = 0;
	char *buffer = malloc(10000);
	char character;
	int rd;
	while((rd = read(fd, &character, 1))){
		buffer[i++] = character;
		if(character == '\n')
			break;
	}
	if(rd == -1 || (!buffer[i - 1] && !rd)){
		free(buffer);
		return NULL;
	}
	buffer[i] = '\0';
	return (buffer);
}

int main(){
	int fd = open("cenas", O_RDONLY);
	char *line;
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
}