/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 02:02:59 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/08/13 19:48:53 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	reset_buf(void *buf)
{
	int	idx;

	idx = 0;
	while (idx < 100)
		((unsigned char *)buf)[idx++] = 0;
}

void	handler(int signum, siginfo_t *info, void *none)
{
	static unsigned char	buf[100];
	static int				str_idx;
	static int				bit_idx;

	(void)none;
	if (bit_idx == 0)
	{
		bit_idx = 8;
		str_idx++;
	}
	if (signum == SIGUSR2)
		buf[str_idx] |= (1 << (bit_idx - 1));
	bit_idx--;
	if ((!buf[str_idx] && !bit_idx) || str_idx == 99)
	{
		write(1, buf, str_idx + 1);
		if (!buf[str_idx] && !bit_idx)
		{
			kill(info->si_pid, SIGUSR1);
			ft_putchar('\n');
		}
		reset_buf(buf);
		str_idx = 0;
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
