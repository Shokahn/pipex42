/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:22:44 by stdevis           #+#    #+#             */
/*   Updated: 2025/01/30 18:28:48 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_error(char *error)
{
	ft_putstr_fd("⛔ Error : ", 2);
	ft_putstr_fd(error, 2);
	exit(1);
}

void	executing_with_path(char *av, char **envp)
{
	char	**cmd;

	cmd = ft_split(av, ' ');
	if (!cmd)
		ft_error("split1 failed\n");
	if (execve(cmd[0], cmd, envp) == -1)
	{
		ft_free_tab(cmd);
		ft_error("execve cmd failed\n");
	}
}

char	*building_the_path(char *dir, char *cmd)
{
	char	*path;
	char	*path_and_cmd;

	path = ft_strjoin(dir, "/");
	path_and_cmd = ft_strjoin(path, cmd);
	free(path);
	if (!path_and_cmd)
		ft_error("join failed\n");
	if (access(path_and_cmd, F_OK) == 0)
		return (path_and_cmd);
	free(path_and_cmd);
	return (NULL);
}

char	*get_path_from_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp[i])
		return (NULL);
	return (envp[i] + 5);
}

char	*find_the_path(char *cmd, char **envp)
{
	char	**possible_paths;
	char	*path;
	char	*path_and_cmd;
	int		i;

	path = get_path_from_env(envp);
	if (!path)
		ft_error("There is no path in the envp\n");
	possible_paths = ft_split(path, ':');
	if (!possible_paths)
		ft_error("split2 failed\n");
	i = 0;
	while (possible_paths[i])
	{
		path_and_cmd = building_the_path(possible_paths[i], cmd);
		if (path_and_cmd)
		{
			ft_free_tab(possible_paths);
			return (path_and_cmd);
		}
		i++;
	}
	ft_free_tab(possible_paths);
	return (NULL);
}
