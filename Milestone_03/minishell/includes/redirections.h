/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ginfranc <ginfranc@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 08:49:21 by ginfranc          #+#    #+#             */
/*   Updated: 2025/09/25 14:55:29 by ginfranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include <fcntl.h>

typedef struct s_oper
{
	int		type;
	char	*value;
	int		fd;
}	t_oper;

typedef struct s_geoper
{
	int		n_opers;
	int		n_erro;
	t_oper	*opers;
	int		*arr;
}	t_geoper;

int		finder_opers(t_geral *geral);
void	counter_opers(t_geral *geral);
t_token	*remove_token(t_geral *geral, t_token *node);
void	free_redirec(t_geral *geral);
int		open_fds(t_geoper *geopers, t_geral *geral);
int		heredoc(t_geral *geral, int i);
void	set_fds(t_geral *geral);
int		init_opers(t_geral *geral);
void	set_fds_utils(t_geral *geral, int j, int i);

#endif
