/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharrold <bharrold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 16:43:24 by bharrold          #+#    #+#             */
/*   Updated: 2020/07/31 22:52:01 by bharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_ping.h"

char*	parse_input(int argc, char **argv, t_ping *p)
{
	struct addrinfo	hints = {.ai_family = AF_INET};
	struct addrinfo *ainfo;

	if (argc > 2 && argv[1][0] == '-' && argv[1][1] == 'v' && argv[1][2] == '\0')
	{
		p->v_mode = 1;
		argv++;
	}
	if (getaddrinfo(argv[1], NULL, &hints, &ainfo))
		return (NULL);
	p->ping_addr.sin_family = PF_INET;
	p->ping_addr.sin_port = 0;
	p->ping_addr.sin_addr.s_addr = ((struct sockaddr_in*)ainfo->ai_addr)->sin_addr.s_addr;
	p->ttl = DEFAULT_TTL;
	freeaddrinfo(ainfo);
	return (argv[1]);
}

int check_input(int argc, char **argv)
{
	return (argc < 2 ||
		(argv[1][0] == '-' && argv[1][1] == 'v' && argv[1][2] == '\0' && argc == 2));
}

void	terminate(int exitcode)
{
	exit(exitcode);
}

int		main(int argc, char **argv)
{
	t_ping ping;


	if (check_input(argc, argv))
	{
		dprintf(2, "Usage: ping [-v] host\n");
		exit(0);
	}
	if ((ping.dest_addr = parse_input(argc, argv, &ping)) == NULL) {
		exit(EXIT_FAILURE);
	}
	if (gen_packet(&ping))
		exit(EXIT_FAILURE);
	printf("EXIT SUCCESS\n");
	return (0);
}
