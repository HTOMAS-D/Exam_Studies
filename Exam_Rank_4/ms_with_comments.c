#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

//simple putstr that write msg to stderr, and appends arg if theres one
int	ft_putstr_2(char *msg, char *arg)
{
    while (*msg)
        write(2, msg++, 1);
    if (arg)
        while (*arg)
            write(2, arg++, 1);
    write(2, "\n", 1);
    return (1);
}

// Function to execute a command
// av is an array of command line arguments
// i is the index of the last argument before a semicolon or pipe
// tmp_fd is the file descriptor of the input stream
// ev is an array of environment variables
int	execute(char **av, int i, int tmp_fd, char **ev)
{
    // Set the i-th argument to NULL
    av[i] = NULL;
    // Replace the standard input with the given file descriptor
    dup2(tmp_fd, STDIN_FILENO);
    // Close the file descriptor
    close(tmp_fd);
    // Execute the command with the given arguments and environment variables
    // If successful, this function does not return
    execve(av[0], av, ev);
    // If execve fails, write an error message to standard error and return 1
    return (ft_putstr_2("error:: cannot execute ", av[0]));
}

int main(int ac, char **av, char **ev)
{
	int fd[2];
	int tmp_fd = dup(STDIN_FILENO); // Duplicate the standard input file descriptor
	int i = 0;
	(void)ac;

	while (av[i] && av[i + 1])
	{
		// Move the pointer to the next command and reset the index
		av = &av[i + 1];
		i = 0;

		// Find the index of the next pipe or semicolon in the command line
		while (av[i] && strcmp(av[i], ";") && strcmp(av[i], "|"))
			i++;
		// Check if the current command is a "cd" command
		if (strcmp(av[0], "cd") == 0)
		{
			// Check that the "cd" command has exactly two arguments
			if (i != 2)
				ft_putstr_2("error: cd: bad arguments", NULL);
			// Call the "chdir" system call to change the current working directory
			else if (chdir(av[1]) != 0)
				ft_putstr_2("error: cd: cannot change directory ", av[1]);
		}
		// If the current command is not a "cd" command
		else if ((i != 0 && av[i] == NULL) || (i != 0 && strcmp(av[i], ";") == 0))
		{
			// Fork a child process to execute the command
			if (fork() == 0)
			{
				// Call the "execute" function to execute the command and handle errors
				if (execute(av, i, tmp_fd, ev))
					return (1);
			}
			else
			{
				// Close the file descriptor for the temporary input file
				close(tmp_fd);

				// Wait for the child process to finish
				while (waitpid(-1, NULL, WUNTRACED) != -1)
					;

				// Duplicate the standard input file descriptor to create a new temporary input file
				tmp_fd = dup(STDIN_FILENO);
			}
		}
		// If the current command is a pipe command
		else if (i != 0 && strcmp(av[i], "|") == 0)
		{
			pipe(fd); // create a pipe
			if (fork() == 0) // if child process
			{
				dup2(fd[1], STDOUT_FILENO); // redirect standard output to the write end of the pipe
				close(fd[0]); // close the read end of the pipe
				close(fd[1]); // close the write end of the pipe
				if (execute(av, i, tmp_fd, ev)) // execute the left-hand side command and check for errors
					return (1);
			}
			else // parent process
			{
				close(tmp_fd); // close the original standard input file descriptor
				close(fd[1]); // close the write end of the pipe
				tmp_fd = fd[0]; // set the new standard input file descriptor to the read end of the pipe
			}
		}
	}
	close(tmp_fd);
	return 0;	
}

