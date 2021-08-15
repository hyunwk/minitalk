/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 23:31:16 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/08/15 18:55:14 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>

// server.c
void	handler(int signum, siginfo_t *info, void *none);

// client.c
void	send_signal(int pid, int n);
void	send_control(int pid, char *str);
void	received_success(int signo);

// print_util.c
void	ft_putnbr(int n);
void	ft_putchar(char c);
void	ft_putstr(char *s);
int		ft_atoi(char *s);
int		ft_strlen(char *s);
#endif
