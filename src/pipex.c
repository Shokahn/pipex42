/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:33:58 by stdevis           #+#    #+#             */
/*   Updated: 2025/01/29 21:50:51 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char *find_the_path(char *cmd, char **envp)
{
	char **possible_paths;
	char *path;
	char *path_and_cmd;
	int i;

	i = 0;
	while(ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	possible_paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while(possible_paths[i])
	{
		path = ft_strjoin(possible_paths[i], "/");
		path_and_cmd = ft_strjoin(path, cmd);
		free(path);
		if (access(path_and_cmd, F_OK) == 0)
		{	
			ft_free_tab(possible_paths);
			return (path_and_cmd);
		}
		free(path_and_cmd);
		i++;
	}
	ft_free_tab(possible_paths);
	return (NULL);
}


void executing(char *av, char **envp)
{
	char **cmd;
	char *path;

	cmd = ft_split(av, ' ');
	path = find_the_path(cmd[0], envp);
	if (!path)
	{
		ft_free_tab(cmd);
		ft_error(BOLD RED"finding path failed"RESET);
	}
	if (execve(path, cmd, envp) == -1)
	{
		ft_free_tab(cmd);		
		ft_error(BOLD RED"execve cmd failed"RESET);
	}
}


void	child(char **av, int *pipe_fd, char **envp)
{
	int infile;
	
	infile = open(av[1], O_RDONLY | O_CREAT);
	if (infile == -1)
		ft_error(BOLD RED"reading infile failed"RESET);
	dup2(pipe_fd[1], 1);
	dup2(infile, 0);
	close(pipe_fd[0]);
	executing(av[2], envp);
	close(pipe_fd[1]);
	close(infile);
}

void	parent(char **av, int *pipe_fd, char **envp)
{
	int outfile;
	
	outfile = open(av[4], O_WRONLY | O_TRUNC | O_CREAT);
	if (outfile == -1)
		ft_error(BOLD RED"reading outfile failed"RESET);
	dup2(pipe_fd[0], 0);
	dup2(outfile, 1);
	close(pipe_fd[1]);
	executing(av[3], envp);
	close(pipe_fd[0]);
	close(outfile);
} 

int main(int ac, char **av, char **envp)
{
	 int pipe_fd[2];
	pid_t pid;

	if (ac != 5)
	{	
		ft_printf(UNDERLINE "↪️  ./pipex <file1> <cmd1> <cmd2> <file2>\n"RESET);
		ft_error(BOLD RED"bad arguments"RESET);
	}
	if (pipe(pipe_fd) == -1)
		ft_error(BOLD RED"pipe fonction failed"RESET);
	pid = fork();
	if (pid == -1)
		ft_error(BOLD RED"fork fonction failed"RESET);
	if (pid == 0)
		child(av, pipe_fd, envp);
	waitpid(pid, NULL, 0);
	parent(av, pipe_fd, envp);
	return(0);
}
