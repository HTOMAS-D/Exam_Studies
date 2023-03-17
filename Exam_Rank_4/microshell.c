#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int BUFFER_SIZE=0;

int	error_msg(char *str, char *arg)
{
	while (*str)
		write(2, str++, 1);
	if (arg)
		while(*arg)
			write(2, arg++, 1);
	write(2, "\n", 1);
	return (1);
}

int ft_execute(char *argv[], int i, int tmp_fd, char *env[])
{
	argv[i] = NULL;
	dup2(tmp_fd, STDIN_FILENO);
	close(tmp_fd);
	execve(argv[0], argv, env);
	return (error_msg("error: cannot execute ", argv[0]));
}

int	main(int ac, char **av, char **envp)
{
	int	i;
	int	fd[2];
	int	tmp_fd;
	(void)ac;

	i = 0;
	tmp_fd = dup(STDIN_FILENO);
	while (av[i] && av[i + 1]) //check if the end is reached
	{
		av = &av[i + 1];	//the new argv start after the ; or |
		i = 0;
		//count until we have all informations to execute the next child;
		while (av[i] && strcmp(av[i], ";") && strcmp(av[i], "|"))
			i++;
		if (strcmp(av[0], "cd") == 0) 
		{
			if (i != 2)
				error_msg("error: cd: bad arguments", NULL);
			else if (chdir(av[1]) != 0)
				error_msg("error: cd: cannot change directory to ", av[1]);
		}
		else if ((i != 0 && av[i] == NULL) || (i != 0 && strcmp(av[i], ";") == 0)) //exec in stdout
		{
			if (fork() == 0)
			{
				if (ft_execute(av, i, tmp_fd, envp))
					return (1);
			}
			else
			{
				close(tmp_fd);
				while(waitpid(-1, NULL, WUNTRACED) != -1)
					;
				tmp_fd = dup(STDIN_FILENO);
			}
		}
		else if(i != 0 && strcmp(av[i], "|") == 0) //pipe
		{
			pipe(fd);
			if (fork() == 0)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
				if (ft_execute(av, i, tmp_fd, envp))
					return (1);
			}
			else
			{
				close(fd[1]);
				close(tmp_fd);
				tmp_fd = fd[0];
			}
		}
	}
	close(tmp_fd);
	return (0);
}