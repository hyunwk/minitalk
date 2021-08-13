/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 02:02:59 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/08/13 14:51:35 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void *reset_buf(void *buf)
{
	int idx;

	idx = 0;
	while (idx < 100)
		((unsigned char *)buf)[idx++] = 0;
	return (buf);
}

void handler(int signum, siginfo_t *info, void *context)
{
	static unsigned char buf[100];
	static int			 str_idx;
	static int			 bit_idx;

	if (bit_idx == 0)
	{
		bit_idx = 8;
		str_idx++;
	}
	if (signum == SIGUSR2)
		buf[str_idx] |= (1 << (bit_idx - 1));
	bit_idx--;
	if (buf[str_idx] == 255 || str_idx == 99)
	{
		write(1, buf, str_idx);
		if (buf[str_idx] == 255)
		{
			kill(info->si_pid, SIGUSR1);
			write(1, "\n", 1);
		}
		reset_buf(buf);	
		str_idx = 0;
	}
}

int main(int argc, char **argv)
{
	struct sigaction act;

	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;
	ft_putstr("server pid : ");
	ft_putnbr(getpid());
	ft_putstr("\nreceived string :");
	if (sigaction(SIGUSR1, &act, NULL))
	{
		ft_putstr("sigaction sigusr1 error\n");
		exit(0);
	}
	if (sigaction(SIGUSR2, &act, NULL))
	{
		ft_putstr("sigaction sigusr2 error\n");
		exit(0);
	}
	while (1)
		;
	return (0);
}

