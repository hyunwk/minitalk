/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 03:03:42 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/08/14 03:03:48 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>

// server.c
void	handler(int signum, siginfo_t *info, void *none);

// client.c
void	send_signal(int pid, int c);
void	send_control(int pid, char *str);
void	received_success(int signo);

// print_util.c
void	ft_putnbr(int n);
void	ft_putchar(char c);
void	ft_putstr(char *s);
int		ft_atoi(char *s);
int		ft_strlen(char *s);
#endif
