/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 02:02:59 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/08/13 22:13:39 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler(int signum, siginfo_t *info, void *none)
{
	static unsigned char	buf;
	static int				bit_idx;

	(void)none;
	if (bit_idx == 0)
	{
		ft_putchar(buf);
		buf = 0;
		bit_idx = 8;
	}
	if (signum == SIGUSR2)
		buf |= (1 << (bit_idx - 1));
	bit_idx--;
	if (!buf && !bit_idx)
	{
		ft_putchar(buf);
		if (!buf && !bit_idx)
		{
			kill(info->si_pid, SIGUSR1);
			ft_putchar('\n');
		}
	}
}

int	main(void)
{
	struct sigaction	act;

	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;
	ft_putstr("server pid : ");
	ft_putnbr(getpid());
	ft_putstr("\nreceived string :");
	if (sigaction(SIGUSR1, &act, 0) || sigaction(SIGUSR2, &act, 0))
	{
		ft_putstr("sigaction error\n");
		exit(1);
	}
	while (1)
		;
	return (0);
}
