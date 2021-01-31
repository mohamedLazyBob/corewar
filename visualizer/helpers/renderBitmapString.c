/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderBitmapString.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesafi <mesafi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 18:49:41 by mesafi            #+#    #+#             */
/*   Updated: 2020/12/17 18:49:46 by mesafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <visualizer.h>

void	renderBitmapString(float x, float y, char *str, int foreground, void *font) {
	int		i;
	float colors[6][3] = {
		{0, 0, 0},
		{1, 1, 1},
		{0.262745098f, 0.380392157f, 0.933333333f},
		{0.988235294f, 0.639215686f, 0.0666666667f},
		{0.709803922f, 0.9901960784f, 0.619607843f},
		{0.929411765f, 0.862745098f, 0.513529412f},
	};

	glColor3f(colors[foreground][0], colors[foreground][1], colors[foreground][2]);
	glRasterPos2f(x, y);
	i = -1;
	while (str[++i])
		glutBitmapCharacter(font, str[i]);
}
