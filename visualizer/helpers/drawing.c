/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesafi <mesafi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 12:46:01 by mesafi            #+#    #+#             */
/*   Updated: 2021/02/03 15:27:32 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static int newCursor = 6;
static int oldCursor = 5;

static void	filler(t_kit *kit, char cursor[64][64], int *processesAlive)
{
	t_process	*node;

	node = kit->procs;
	while (node != NULL)
	{
		cursor[(node->op_pc) % 64][(node->op_pc) / 64] = newCursor;
		// cursor[(node->op_pc - 1) % 64][(node->op_pc - 1) / 64] = oldCursor;
		node = node->next;
		*processesAlive += 1;
	}
}

static int	getBackground(char cursor, int playerId)
{
	if (cursor == newCursor)
		return (newCursor);
	else
		return (playerId);
}

static int	putInformation(t_kit *kit, int processesAlive)
{
	char	buffer[500];
	int		i;
	int		padding;
	int		live_counter;

	i = -1;
	live_counter = 0;
	while (++i < kit->bloc->players_counter)
	{
		live_counter += kit->live[i][0];
	}
	sprintf(buffer, "Total cycle :                %d", kit->game_params->total_cycles_counter);
	renderBitmapString(470, 590, buffer, 1, GLUT_BITMAP_9_BY_15);
	sprintf(buffer, "Cycle to die :               %d", kit->game_params->cycles_to_die);
	renderBitmapString(470, 550, buffer, 1, GLUT_BITMAP_9_BY_15);
	sprintf(buffer, "Live counter :               %d", live_counter);
	renderBitmapString(470, 510, buffer, 1, GLUT_BITMAP_9_BY_15);
	sprintf(buffer, "Processes slive :            %d", processesAlive);
	renderBitmapString(470, 470, buffer, 1, GLUT_BITMAP_9_BY_15);

	i = -1;
	while (++i < kit->bloc->players_counter)
	{
		padding = i * 100;

		sprintf(buffer, "Player %d :", -i - 1);
		renderBitmapString(470, 390 - padding, buffer, 1, GLUT_BITMAP_9_BY_15);

		sprintf(buffer, "%s", kit->bloc->players[i].header.prog_name);
		renderBitmapString(580, 390 - padding, buffer, 2 + i, GLUT_BITMAP_9_BY_15);

		sprintf(buffer, "Last live :                   %d", kit->live[i][1]);
		renderBitmapString(490, 390 - 30 - padding, buffer, 1, GLUT_BITMAP_9_BY_15);

		sprintf(buffer, "Lives in current period :     %d", kit->live[i][0]);
		renderBitmapString(490, 390 - 60 - padding, buffer, 1, GLUT_BITMAP_9_BY_15);
	}
	return (i);
}

static void	keysUsage()
{
	char	buffer[500];

	sprintf(buffer, "Start/Pause : 'SPACE'");
	renderBitmapString(470, -470, buffer, 1, GLUT_BITMAP_9_BY_15);
	sprintf(buffer, "Exit : 'ESC'");
	renderBitmapString(470, -510, buffer, 1, GLUT_BITMAP_9_BY_15);
	sprintf(buffer, "Step Up: 'arrow up / right'");
	renderBitmapString(470, -550, buffer, 1, GLUT_BITMAP_9_BY_15);
	sprintf(buffer, "Step Down: 'arrow down / left'");
	renderBitmapString(470, -590, buffer, 1, GLUT_BITMAP_9_BY_15);
}

static void	progressBar(t_kit *kit, int percent[4])
{
	int		i;
	int		result;
	int		indexes[2] = {0};

	i = -1;
	result = 0;
	while (++i < kit->bloc->players_counter)
		result += percent[i];
	i = -1;
	while (++i < kit->bloc->players_counter)
	{
		if (indexes[0] == 0)
			indexes[0] = 460;
		indexes[1] = 410 - (kit->bloc->players_counter * 120);
		rectangle(indexes[0], indexes[1], indexes[0] + percent[i] * 350 / result, indexes[1] + 20, i + 1);
		indexes[0] += percent[i] * 350 / result;
	}
}

static void	getPercent(int percent[4], int playerId)
{
	if (playerId > 0 && playerId < 5)
		percent[playerId - 1] += 1;
}

static void	winner(t_kit *kit)
{
	char	buffer[500];
	int		i;

	i = 410 - (kit->bloc->players_counter * 120) - 70;
	sprintf(buffer, "\"%s\", has won !", kit->bloc->players[kit->last_live - 1].header.prog_name);
	renderBitmapString(470, i, buffer, 1, GLUT_BITMAP_9_BY_15);
}

void		drawing(t_dlist *node)
{
	int		i;
	int		x;
	int		y;
	t_kit	*kit;
	char	hex[3];
	int		percent[4] = {0};
	char	cursor[64][64] = {0};
	int		processesAlive = 0;
	int		background;

	kit = (t_kit *)(node->content);
	i = -1;
	filler(kit, cursor, &processesAlive);
	while (++i < MEM_SIZE)
	{
		x = (i % 64);
		y = (i / 64);
		background = getBackground(cursor[x][y], kit->procs->arena[1][i] == 0 \
			? kit->procs->arena[1][i] : (kit->procs->arena[1][i] - 1) ^ 0xFF);
		getPercent(percent, (kit->procs->arena[1][i] - 1) ^ 0xFF);
		x = x + (19 * x) - (WIDTH / 2);
		y = y - (21 * y) + (HEIGHT / 2);
		rectangle(x, y, x + 19, y - 19, background);
		if (kit->procs->arena[1][i])
		{
			sprintf(hex, "%02X", kit->procs->arena[0][i]);
			hex[2] = 0;
			renderBitmapString(x + 2, y - 14, hex, 0, GLUT_BITMAP_HELVETICA_12);
		}
	}
	putInformation(kit, processesAlive);
	progressBar(kit, percent);
	if (!node->next && !kit->last_live)
		winner(kit);
	keysUsage();
}
