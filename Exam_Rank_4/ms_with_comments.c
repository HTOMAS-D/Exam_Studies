#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

// A function to print a string to standard error (file descriptor 2)
int	ft_putstr_2(char *msg, char *arg)
{
	while (*msg)
		write(2, msg++, 1); // Write one character of the message at a time to stderr
	if (arg)
		while (*arg)
			write(2, arg++, 1); // Write one character of the argument at a time to stderr
	write(2, "\n", 1); // Write a newline character to stderr
	return (1);
}

// A function to execute a command with its arguments and environment variables
// i is the index of the last argument before a semicolon or pipe character
// tmp_fd is the file descriptor to use as stdin for the command
int	execute(char **av, int i, int tmp_fd, char **ev)
{
	av[i] = NULL; // Set the argument after the semicolon or pipe character to NULL to terminate the argument list
	dup2(tmp_fd, STDIN_FILENO); // Replace stdin (file descriptor 0) with tmp_fd
	close(tmp_fd); // Close tmp_fd
	execve(av[0], av, ev); // Execute the command with its arguments and environment variables
	return (ft_putstr_2("error:: cannot execute ", av[0])); // Print an error message if execve returns
}

int main(int ac, char **av, char **ev)
{
	int fd[2]; // An array to store two file descriptors for a pipe
	int tmp_fd = dup(STDIN_FILENO); // Duplicate stdin to create a temporary file descriptor for input
	int i = 0; // A variable to store the index of the current argument
	(void)ac; // Ignore the unused argument count parameter
	while (av[i] && av[i + 1]) // Loop through the arguments until the end or the second last argument
	{
		av = &av[i + 1]; // Move the av pointer to the next argument after the semicolon or pipe character
		i = 0; // Reset the index of the current argument to 0
		while (av[i] && strcmp(av[i], ";") && strcmp(av[i], "|")) // Loop through the arguments until the end or a semicolon or pipe character is found
			i++;
		if (strcmp(av[0], "cd") == 0) // Check if the command is cd
		{
			if (i != 2)
				ft_putstr_2("error: cd: bad arguments", NULL); // Print an error message if the number of arguments is not 2
			else if (chdir(av[1]) != 0)
				ft_putstr_2("error: cd: cannot change directory ", av[1]); // Print an error message if chdir returns an error
		}
		else if ((i != 0 && av[i] == NULL) || (i != 0 && strcmp(av[i], ";") == 0)) // Check if a semicolon character is found or the end of the argument list is reached
		{
			if (fork() == 0) // Create a child process to execute the command
			{
				if (execute(av, i, tmp_fd, ev)) // Call the execute function and print an error message if it returns
					return (1);
			}
			else // In the parent process
			{
				close(tmp_fd); // Close the temporary file descriptor
				while (waitpid(-1, NULL, WUN
