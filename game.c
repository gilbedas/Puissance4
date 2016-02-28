/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atheveno <atheveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 15:45:47 by atheveno          #+#    #+#             */
/*   Updated: 2016/02/28 13:39:05 by ghery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include <time.h>
#include <stdlib.h>
//#include "libft.h"
#define DEBUG	write(1, "DEBUG", 5);
#define COLORJ1 "\x1B[31m0\033[0m"
#define COLORJ2 "\x1B[33m0\033[0m"

typedef struct	s_init {
	char		**map;
	char		*j1;
	char		*j2;
	int			x;
	int			y;
}				t_init;

char	**init_map(t_init *t);
void	print_map2(t_init *t);
void	ft_putdown(t_init *t);
int		play(t_init *t, int player);
int		win(t_init t);
int		rand_player(void);

int		get_int(char *arg)
{
	int index;

	index = 0;
	while (arg[index])
	{
		if (!ft_isdigit(arg[index]))
		{
			ft_printf("Le caractere %c est incorrect.\n", arg[index]);
			return (-1);
		}
		index++;
	}
	return (ft_atoi(arg));
}

int main(int argc, char **argv)
{
	t_init t;
	int	num;
	int player;

	player = rand_player();
	t.j1 = ft_strdup(COLORJ1);
	t.j2 = ft_strdup(COLORJ2);
	t.x = 7;
	t.y = 6;
	if (!(argc == 1) && !(argc == 3))
		ft_printf("Vous avez rentrer le mauvais nombre d'arguments.\n");
	else
	{
		if (argc == 3)
		{
			if (get_int(argv[1]) >= t.x && get_int(argv[2]) >= t.y)
			{
				t.x = get_int(argv[1]);
				t.y = get_int(argv[2]);
			}
			else
			{
				ft_printf("Taille incorrecte.\n");
				return (0);
			}
		}
		t.map = init_map(&t);
		while (42)
		{
			print_map2(&t);
			if (win(t) == 1)
			{
				if (player == 1)
					ft_printf("le joueur %c a gagner\n", 'R');
				if (player == 0)
					ft_printf("le joueur %c a gagner\n", 'J');
				return (0);
			}
			else if (win(t) == 2)
			{
				ft_printf("egalite !\n");
				return (0);
			}
			if (player == 0)
				player = 1;
			else
				player = 0;
			if (play(&t, player))
				;
			else
				return (0);
		}
		ft_printf("X = %d \t Y = %d\n", t.x, t.y);
		print_map2(&t);
	}
	return (0);
}

char		**init_map(t_init *t)
{
	char	**map;
	int 	i;
	int		j;

	i = -1;
	map = (char **)malloc(sizeof(char *) * (t->y + 1));
	while (++i < t->y + 1)
		map[i] = (char *)malloc(sizeof(char) * t->x);
	j = -1;
	while (++j < t->y)
	{
		i = -1;
		while (++i < t->x)
			map[j][i] = '.';
	}
	return (map);
}

void		print_map2(t_init *t)
{
	int		i;
	int		j;

	j = -1;
	while (++j < t->y)
	{
		i = -1;
		ft_printf("%5d", j + 1);
		while (++i < t->x)
		{
			//			ft_printf("%s", t->j2);
			ft_printf("%5c", t->map[j][i]);
		}
		ft_printf("\n");
	}
	ft_printf("%5 ");
	i = 0;
	while (++i <= t->x)
		ft_printf("%5d", i);
	ft_printf("\n");
}

int			play(t_init *t, int player)
{
	char	**coup;
	int		num;

	if (!(coup = (char **)malloc(sizeof(char *))))
	{
		ft_printf("Erreur de Malloc\n");
		return (0);
	}
	get_next_line(0, coup);
	if ((num = get_int(*coup)))
	{
		if (num > t->x || t->map[0][num - 1] != '.')
		{
			ft_printf("coup invalide\n");
			return (1);
		}
		//ft_printf("fuck off");
		else
		{
			ft_printf("%d\n", num);
			if (player == 1)
				t->map[0][num - 1] = 'R';
			else if (player == 0)
				t->map[0][num - 1] = 'J';
			ft_putdown(t);
			return (1);
		}
	}
	return (0);
}

void	ft_putdown(t_init *t)
{
	int j;
	int i;

	i = 0;
	while (i < t->x)
	{
		j = 0;
		while (j < t->y)
		{
			if (t->map[j][i] != '.')
			{
				if (t->map[j + 1][i] == '.')
				{
					t->map[j + 1][i] = t->map[j][i];
					t->map[j][i] = '.';
				}
			}
			j++;
		}
		i++;
	}
}

int		win(t_init t)
{
	int		i;
	int		j;
	int		count;
	int		point;
	int		k;

	j = 0;
	point = 0;
	k = 0;
	while (j < t.y)
	{
		i = 0;
		while (i < t.x)
		{
			if (t.map[j][i] != '.')
			{
				count = 0;
				while (t.map[j][i + (count++)] == t.map[j][i])
					if (count == 4)
						return (1);
				count = 0;
				while (t.map[j + (count++)][i] == t.map[j][i])
					if (count == 4)
						return (1);
				count = 1;
				while (t.map[j + count][i + count] == t.map[j][i])
				{
					if (count == 3)
						return(1);
					count++;
				}
				count = 1;
				if (j - 4 >= 0)
					while (t.map[j - count][i + count] == t.map[j][i])
					{
						if (count == 3)
							return (1);
						count++;
					}
			}
			if (t.map[j][i] == '.')
				point++;
			i++;
		}
		j++;
	}
	if (point == 0)
		return (2);
	ft_printf("il sort\n");
	return (0);
}

int		rand_player(void)
{
	int		player;

	srand(time(NULL));
	player = rand() % 2;
	return (player);
}
