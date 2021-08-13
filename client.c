/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 02:03:12 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/08/13 19:53:54 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_signal(int pid, int c)
{
	if (c == 0)
		kill(pid, SIGUSR1);
	else if (c == 1)
		kill(pid, SIGUSR2);
	usleep(50);
}

void	send_control(int pid, char *str)
{
	int	idx;
	int	close_idx;
	int	c;
	int	digit;

	idx = 0;
	close_idx = 0;
	while (str[idx])
	{
		c = (unsigned char)str[idx++];
		digit = 8;
		while (--digit >= 0)
		{
			if (c & 1 << digit)
				send_signal(pid, 1);
			else
				send_signal(pid, 0);
		}
	}
	while (close_idx++ <= 7)
		send_signal(pid, 0);
}

void	received_success(int signo)
{
	(void)signo;
	ft_putstr("success");
	exit(0);
}

int	main(int argc, char **argv)
{
	if (argc == 3)
	{
		signal(SIGUSR1, received_success);
		ft_putstr("server pid :");
		ft_putstr(argv[1]);
		ft_putstr("\nsend_control string : ");
		ft_putstr(argv[2]);
		ft_putstr("\nlen : ");
		ft_putnbr(ft_strlen(argv[2]));
		ft_putstr("\nserver response : ");
		send_control(ft_atoi(argv[1]), argv[2]);
	}
	else
	{
		ft_putstr("usage error : ");
		ft_putstr(argv[0]);
	}
	return (0);
}
