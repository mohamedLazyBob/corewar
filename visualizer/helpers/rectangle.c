/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rectangle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesafi <mesafi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 18:49:34 by mesafi            #+#    #+#             */
/*   Updated: 2020/12/17 18:49:36 by mesafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <visualizer.h>

void	rectangle(int x1, int y1, int x2, int y2, int background)
{
	// How to Convert from RGB 255 to OpenGL Float Color
	// color = [237, 220, 210].map(x => x / 255)
	float colors[7][3] = {
		{0.0784313725f, 0.129411765f, 0.180392157f},
		{0.262745098f, 0.380392157f, 0.933333333f},
		{0.988235294f, 0.639215686f, 0.0666666667f},
		{0.709803922f, 0.9901960784f, 0.619607843f},
		{0.929411765f, 0.862745098f, 0.513529412f},
		{0.82745098f, 0.82745098f, 0.82745098f},
		{1, 1, 1},
	};

	glBegin(GL_QUADS);
		glColor3f(colors[background][0], colors[background][1], colors[background][2]);
		glVertex2f(x1, y1);
		glVertex2f(x2, y1);
		glVertex2f(x2, y2);
		glVertex2f(x1, y2);
	glEnd();
}
