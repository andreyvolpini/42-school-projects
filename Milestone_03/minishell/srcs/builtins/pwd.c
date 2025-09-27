/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@udent.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 08:53:09 by avolpini          #+#    #+#             */
/*   Updated: 2025/09/13 08:53:09 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_geral *geral)
{
	char	*cwd;

	cwd = geral->vars.pwd;
	if (!cwd)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", cwd);
	return (0);
}
