/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:33:58 by stdevis           #+#    #+#             */
/*   Updated: 2025/01/31 14:53:40 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	executing(char *av, char **envp)
{
	char	**cmd;
	char	*path;
	char	**split;

	split = ft_split(av, ' ');
	if (!split)
		ft_error("split3 failed\n");
	if (access(split[0], F_OK) == 0)
		executing_with_path(av, envp);
	cmd = ft_split(av, ' ');
	if (!cmd)
		ft_error("split4 failed\n");
	path = find_the_path(cmd[0], envp);
	if (!path)
	{
		ft_free_tab(cmd);
		ft_error("finding path failed\n");
	}
	if (execve(path, cmd, envp) == -1)
	{
		ft_free_tab(cmd);
		ft_perror("execve cmd failed\n");
	}
}

void	child(char **av, int *pipe_fd, char **envp)
{
	int	infile;

	infile = open(av[1], O_RDONLY);
	if (infile == -1)
		ft_perror("reading infile failed\n");
	dup2(pipe_fd[1], 1);
	dup2(infile, 0);
	close(pipe_fd[0]);
	executing(av[2], envp);
}

void	parent(char **av, int *pipe_fd, char **envp)
{
	int	outfile;

	outfile = open(av[4], O_RDONLY | O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (outfile == -1)
		ft_perror("reading outfile failed\n");
	dup2(pipe_fd[0], 0);
	dup2(outfile, 1);
	close(pipe_fd[1]);
	executing(av[3], envp);
}

int	main(int ac, char **av, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (ac != 5)
	{
		ft_putstr_fd("⛔ Error : bad arguments\n", 2);
		ft_putstr_fd("↪️ ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
		exit(1);
	}
	if (pipe(pipe_fd) == -1)
		ft_perror("pipe fonction failed");
	pid = fork();
	if (pid == -1)
		ft_perror("fork fonction failed");
	if (pid == 0)
		child(av, pipe_fd, envp);
	waitpid(pid, NULL, 0);
	parent(av, pipe_fd, envp);
	return (0);
}
