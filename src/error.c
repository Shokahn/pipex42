/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:49:14 by stdevis           #+#    #+#             */
/*   Updated: 2025/01/31 14:50:36 by stdevis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_error(char *error)
{
	ft_putstr_fd("⛔ Error : ", 2);
	ft_putstr_fd(error, 2);
	exit(1);
}

void	ft_perror(char *error)
{
	perror(error);
	exit(1);
}
