#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

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

int	execute(char **av, int i, int tmp_fd, char **ev)
{
	av[i] = NULL;
	dup2(tmp_fd, STDIN_FILENO);
	close(tmp_fd);
	execve(av[0], av, ev);
	return (ft_putstr_2("error:: cannot execute ", av[0]));
}

int main(int ac, char **av, char **ev)
{
	int fd[2];
	int tmp_fd = dup(STDIN_FILENO);
	int i = 0;
	(void)ac;
	while (av[i] && av[i + 1])
	{
		av = &av[i + 1];
		i = 0;
		while (av[i] && strcmp(av[i], ";") && strcmp(av[i], "|"))
			i++;
		if (strcmp(av[0], "cd") == 0)
		{
			if (i != 2)
				ft_putstr_2("error: cd: bad arguments", NULL);
			else if (chdir(av[1]) != 0)
				ft_putstr_2("error: cd: cannot change directory ", av[1]);
		}
		else if ((i != 0 && av[i] == NULL) || (i != 0 && strcmp(av[i], ";") == 0))
		{
			if (fork() == 0)
			{
				if (execute(av, i, tmp_fd, ev))
					return (1);
			}
			else
			{
				close(tmp_fd);
				while (waitpid(-1, NULL, WUNTRACED) != -1)
					;
				tmp_fd = dup(STDIN_FILENO);
			}
		}
		else if (i != 0 && strcmp(av[i], "|") == 0)
		{
			pipe(fd);
			if (fork() == 0)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
				if (execute(av, i, tmp_fd, ev))
					return (1);
			}
			else
			{
				close(tmp_fd);
				close(fd[1]);
				tmp_fd = fd[0];
			}
		}
	}
	close(tmp_fd);
	return (0);
}